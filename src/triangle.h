#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "quad.h"

class triangle : public quad {
  public:
    triangle(const point3& corner, const vec3& side_a, const vec3& side_b, shared_ptr<material> mat)
      : quad(corner, side_a, side_b, mat) {}

    virtual bool is_intersection_in_bounds(double a, double b, hit_record& rec) const {
      if (a < 0 || b < 0 || a + b > 1) return false;
      rec.u = a;
      rec.v = b;
      return true;
    }
};

#endif
