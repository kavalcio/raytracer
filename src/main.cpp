#include "main.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

color sky_color = color(0.5, 0.7, 1.0);
color ground_color = color(1.0, 1.0, 1.0);

// TODO: add specular reflection
int main() {
  // World

  hittable_list world;

  auto material_ground = make_shared<lambertian>(color(0.8, 0.8, 0.0));
  auto material_center = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  auto material_left   = make_shared<dielectric>(1.50);
  auto material_bubble = make_shared<dielectric>(1.00 / 1.50);
  auto material_right  = make_shared<dielectric>(1.2);

  world.add(make_shared<sphere>(point3( 0.0, -100.5, -1.0), 100.0, material_ground));
  world.add(make_shared<sphere>(point3( 0.0,    0.0, -1.2),   0.5, material_center));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.5, material_left));
  world.add(make_shared<sphere>(point3(-1.0,    0.0, -1.0),   0.4, material_bubble));
  world.add(make_shared<sphere>(point3( 1.0,    0.0, -1.0),   0.5, material_right));

  // Camera

  camera cam;
  cam.image_width = 400;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
}
