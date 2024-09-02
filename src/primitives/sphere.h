#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"

class sphere : public hittable {
  public:
    // Stationary sphere
    sphere(const point3& center, double radius, shared_ptr<material> mat)
      : center(center), radius(std::fmax(0,radius)), mat(mat), is_moving(false) {
        vec3 r_vec = vec3(radius, radius, radius);
        bbox = aabb(center - r_vec, center + r_vec);
      }

    // Moving sphere
    sphere(const point3& center, double radius, shared_ptr<material> mat, const vec3& velocity)
      : center(center), radius(std::fmax(0,radius)), mat(mat), is_moving(true), velocity(velocity) {
        vec3 r_vec = vec3(radius, radius, radius);
        vec3 center2 = center + velocity;
        aabb box1 = aabb(center - r_vec, center + r_vec);
        aabb box2 = aabb(center2 - r_vec, center2 + r_vec);
        bbox = aabb(box1, box2);
      }

    /*
      Derived from the equation for a sphere and the quadratic formula,
      this function determines if a ray intersects a sphere.
    */
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
      point3 adjusted_center = is_moving ? sphere_center(r.time()) : center;
      vec3 oc = adjusted_center - r.origin();
      auto a = r.direction().length_squared();
      auto h = dot(r.direction(), oc);
      auto c = oc.length_squared() - radius*radius;

      auto discriminant = h*h - a*c;
      if (discriminant < 0)
        return false;

      auto sqrtd = std::sqrt(discriminant);

      // Find the nearest root that lies in the acceptable range.
      auto root = (h - sqrtd) / a;
      if (!ray_t.surrounds(root)) {
        root = (h + sqrtd) / a;
        if (!ray_t.surrounds(root))
          return false;
      }

      rec.t = root;
      rec.p = r.at(rec.t);
      vec3 outward_normal = (rec.p - adjusted_center) / radius;
      rec.set_face_normal(r, outward_normal);
      get_sphere_uv(outward_normal, rec.u, rec.v);
      rec.mat = mat;

      return true;
    }

    aabb bounding_box() const override { return bbox; }

  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
    vec3 velocity;
    bool is_moving;
    aabb bbox;

    point3 sphere_center(double time) const {
      // Linearly interpolate from center to center + velocity according to time
      return center + (time * velocity);
    }

    static void get_sphere_uv(const point3& p, double& u, double& v) {
      // p: a given point on the sphere of radius one, centered at the origin.
      // u: returned value [0,1] of angle around the Y axis from X=-1.
      // v: returned value [0,1] of angle from Y=-1 to Y=+1.
      //     <1 0 0> yields <0.50 0.50>       <-1  0  0> yields <0.00 0.50>
      //     <0 1 0> yields <0.50 1.00>       < 0 -1  0> yields <0.50 0.00>
      //     <0 0 1> yields <0.25 0.50>       < 0  0 -1> yields <0.75 0.50>

      auto theta = std::acos(-p.y());
      auto phi = std::atan2(-p.z(), p.x()) + pi;

      u = phi / (2 * pi);
      v = theta / pi;
    }
};

#endif
