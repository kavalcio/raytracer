#include "main.h"
#include "bvh.h"
#include "perlin.h"
#include "hittable_list.h"
#include "primitives/sphere.h"
#include "primitives/quad.h"
#include "primitives/triangle.h"
#include "camera.h"
#include "primitives/triangle_mesh.h"

// scenes
#include "scenes/part_1_final_scene.h"
#include "scenes/bouncing_spheres.h"
#include "scenes/checkered_spheres.h"
#include "scenes/earth.h"
#include "scenes/quads_scene.h"
#include "scenes/teapot_scene.h"
#include "scenes/cornell_box_scene.h"
#include "scenes/perlin_spheres.h"

// TODO: add ability to output to something other than ppm file
// TODO: add class descriptions to each .h file
// TODO: add runtime params for resolution, samples per pixel, scene number
// TODO: add specular reflection
// TODO: add fresnel reflection
// TODO: add beer's law: https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
// TODO: check out further readings: https://github.com/RayTracing/raytracing.github.io/wiki/Further-Readings
int main() {
  perlin_spheres();
}
