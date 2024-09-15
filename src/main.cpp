#include "main.h"
#include "bvh.h"
#include "perlin.h"
#include "hittable_list.h"
#include "primitives/sphere.h"
#include "primitives/quad.h"
#include "primitives/triangle.h"
#include "camera.h"
#include "primitives/triangle_mesh.h"
#include "scenes/index.h"

// TODO: add ability to output to something other than ppm file
// TODO: add class descriptions to each .h file
// TODO: add runtime params for resolution, samples per pixel, scene number
// TODO: do some performance benchmarking
// TODO: add specular reflection
// TODO: add fresnel reflection
// TODO: add beer's law: https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
// TODO: check out further readings: https://github.com/RayTracing/raytracing.github.io/wiki/Further-Readings
int main(int argc, char * argv[]) {
  switch (4) {
    case 1: s_part_1_final(); break;
    case 2: s_bouncing_spheres(); break;
    case 3: s_checkered_spheres(); break;
    case 4: s_earth(); break;
    case 5: s_quads(); break;
    case 6: s_teapot(); break;
    case 7: s_cornell_box(); break;
    case 8: s_perlin_spheres(); break;
    default:
      std::cerr << "Invalid scene number" << std::endl;
      break;
  }
}
