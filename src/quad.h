#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"

// TODO: add velocity + motion blur to quads
class quad : public hittable {
  public:
    quad(const point3& Q, const vec3& u, const vec3& v, shared_ptr<material> mat)
      : Q(Q), u(u), v(v), mat(mat) {
        auto n = cross(u, v);
        plane_normal = unit_vector(n);
        D = dot(plane_normal, Q);
        w = n / dot(n,n);

        set_bounding_box();
      }

    virtual void set_bounding_box() {
      // Compute the bounding box of all four vertices.
      // We need to factor in both diagonals because the quad is in 3D space, and it may not be axis-aligned.
      auto bbox_diagonal1 = aabb(Q, Q + u + v);
      auto bbox_diagonal2 = aabb(Q + u, Q + v);
      bbox = aabb(bbox_diagonal1, bbox_diagonal2);
    }

    aabb bounding_box() const override { return bbox; }

    /*
      The intersection of a ray with a plane is given by the equation:
      t = (D - dot(n,  P)) / dot(n, d)
      where:
        - t is the ray parameter at the intersection point
        - D is the distance from the origin to the plane
        - n is the normal vector of the plane
        - P is the origin point of the ray
        - d is the direction vector of the ray
    */
    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
      auto denom = dot(plane_normal, r.direction());

      // No hit if the ray is parallel to the plane.
      if (std::fabs(denom) < 1e-8) return false;

      // Return false if the hit point parameter t is outside the ray interval.
      auto t = (D - dot(plane_normal, r.origin())) / denom;
      if (!ray_t.contains(t)) return false;

      // Determine if the hit point lies within the planar shape using its plane coordinates.
      auto intersection = r.at(t);
      vec3 plane_intersection_vector = intersection - Q;
      auto alpha = dot(w, cross(plane_intersection_vector, v));
      auto beta = dot(w, cross(u, plane_intersection_vector));

      if (!is_interior(alpha, beta, rec)) return false;

      // Ray hits the 2D shape; set the rest of the hit record and return true.
      rec.t = t;
      rec.p = intersection;
      rec.mat = mat;
      rec.set_face_normal(r, plane_normal);

      return true;
    }

    virtual bool is_interior(double a, double b, hit_record& rec) const {
      interval unit_interval = interval(0, 1);
      // Given the hit point in plane coordinates, return false if it is outside the
      // primitive, otherwise set the hit record UV coordinates and return true.

      if (!unit_interval.contains(a) || !unit_interval.contains(b))
        return false;

      rec.u = a;
      rec.v = b;
      return true;
    }

  private:
    point3 Q;
    vec3 u, v;
    vec3 w;
    shared_ptr<material> mat;
    aabb bbox;
    vec3 plane_normal;
    double D;
};

#endif
