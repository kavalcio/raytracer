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

  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

  // Camera

  camera cam;
  cam.image_width = 400;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  cam.render(world);
}
