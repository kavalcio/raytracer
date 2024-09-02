#ifndef AABB_H
#define AABB_H

#include "main.h"

class aabb {
  public:
    interval x, y, z;

    aabb() {}

    aabb(const interval& x, const interval& y, const interval& z)
      : x(x), y(y), z(z) 
    {
      pad_to_minimums();
    }

    aabb(const point3& a, const point3& b) {
      // Treat the two points a and b as extrema for the bounding box, so we don't require a
      // particular minimum/maximum coordinate order.

      x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
      y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
      z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
      
      pad_to_minimums();
    }

    aabb(const aabb& a, const aabb& b)
      : x(a.x, b.x), y(a.y, b.y), z(a.z, b.z) {}
    // aabb(const aabb& box0, const aabb& box1) {
    //   x = interval(box0.x, box1.x);
    //   y = interval(box0.y, box1.y);
    //   z = interval(box0.z, box1.z);
    // }

    const interval& axis_interval(int n) const {
      if (n == 1) return y;
      if (n == 2) return z;
      return x;
    }

    bool hit(const ray& r, interval ray_t) const {
      // Slab method for AABB intersection

      const point3& ray_orig = r.origin();
      const vec3& ray_dir  = r.direction();
      for (int n = 0; n < 3; n++) {
        const interval& n_interval = axis_interval(n);

        double t0 = (n_interval.min - ray_orig[n]) / ray_dir[n];
        double t1 = (n_interval.max - ray_orig[n]) / ray_dir[n];

        if (t0 < t1) {
          if (t0 > ray_t.min) ray_t.min = t0;
          if (t1 < ray_t.max) ray_t.max = t1;
        } else {
          if (t1 > ray_t.min) ray_t.min = t1;
          if (t0 < ray_t.max) ray_t.max = t0;
        }

        if (ray_t.max <= ray_t.min)
          return false;
      }
      return true;
    }

    int longest_axis() const {
      // Returns the index of the longest axis of the bounding box.

      if (x.size() > y.size())
        return x.size() > z.size() ? 0 : 2;
      else
        return y.size() > z.size() ? 1 : 2;
    }

    static const aabb empty, universe;


  private:
    void pad_to_minimums() {
      // Adjust the AABB so that no side is narrower than some delta, padding if necessary.
      double delta = 0.0001;
      if (x.size() < delta) x = x.expand(delta);
      if (y.size() < delta) y = y.expand(delta);
      if (z.size() < delta) z = z.expand(delta);
    }
};

const aabb aabb::empty = aabb(interval::empty, interval::empty, interval::empty);
const aabb aabb::universe = aabb(interval::universe, interval::universe, interval::universe);

#endif
