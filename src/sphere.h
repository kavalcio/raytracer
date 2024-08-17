#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
  public:
    // Stationary sphere
    sphere(const point3& center, double radius, shared_ptr<material> mat)
      : center(center), radius(std::fmax(0,radius)), mat(mat), is_moving(false) {}

    // Moving sphere
    sphere(const point3& center, double radius, shared_ptr<material> mat, const vec3& velocity)
      : center(center), radius(std::fmax(0,radius)), mat(mat), is_moving(true), velocity(velocity) {}

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
      rec.mat = mat;

      return true;
    }

  private:
    point3 center;
    double radius;
    shared_ptr<material> mat;
    vec3 velocity;
    bool is_moving;

    point3 sphere_center(double time) const {
      // Linearly interpolate from center to center + velocity according to time
      return center + (time * velocity);
    }
};

#endif
