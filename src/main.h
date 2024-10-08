#ifndef MAIN_H
#define MAIN_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>

// C++ Std Usings

using std::make_shared;
using std::shared_ptr;

// Constants

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utility Functions

inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double() {
  // Returns a random real in [0,1).
  return std::rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max) {
  // Returns a random real in [min,max).
  return min + (max-min)*random_double();
}

inline int random_int(int min, int max) {
  // Returns a random integer in [min,max].
  return int(random_double(min, max+1));
}

// Common Headers

#include "interval.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"

#include "bvh.h"
#include "perlin.h"
#include "camera.h"
#include "hittable_list.h"
#include "primitives/sphere.h"
#include "primitives/quad.h"
#include "primitives/triangle.h"
#include "primitives/triangle_mesh.h"
#include "primitives/constant_medium.h"

#endif
