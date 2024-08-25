#include "main.h"
#include "bvh.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

// scenes
#include "scenes/part_1_final_scene.h"
# include "scenes/bouncing_spheres.h"

// TODO: add runtime params for resolution and samples per pixel
// TODO: add geometries other than sphere
// TODO: add specular reflection
// TODO: add fresnel reflection
// TODO: add beer's law
// https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
int main() {
  bouncing_spheres();
}
