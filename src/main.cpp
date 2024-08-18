#include "main.h"
#include "bvh.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

color sky_color = color(0.5, 0.7, 1.0);
color ground_color = color(1.0, 1.0, 1.0);

// TODO: add runtime params for resolution and samples per pixel
// TODO: add geometries other than sphere
// TODO: add specular reflection
// TODO: add fresnel reflection
// TODO: add beer's law
// https://blog.demofox.org/2017/01/09/raytracing-reflection-refraction-fresnel-total-internal-reflection-and-beers-law/
int main() {
  // World

  hittable_list world;

  auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

  for (int a = -11; a < 11; a++) {
    for (int b = -11; b < 11; b++) {
      auto choose_mat = random_double();
      point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

      if ((center - point3(4, 0.2, 0)).length() > 0.9) {
        shared_ptr<material> sphere_material;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = color::random() * color::random();
          sphere_material = make_shared<lambertian>(albedo);
          vec3 velocity = vec3(0, random_double(0, 0.5), 0);
          world.add(make_shared<sphere>(center, 0.2, sphere_material, velocity));
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = color::random(0.5, 1);
          auto fuzz = random_double(0, 0.5);
          sphere_material = make_shared<metal>(albedo, fuzz);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        } else {
          // glass
          sphere_material = make_shared<dielectric>(1.5);
          world.add(make_shared<sphere>(center, 0.2, sphere_material));
        }
      }
    }
  }

  auto material1 = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

  auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
  world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

  auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
  world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

  world = hittable_list(make_shared<bvh_node>(world));

  // Camera

  camera cam;

  cam.aspect_ratio      = 16.0 / 9.0;
  cam.image_width       = 400;
  cam.samples_per_pixel = 50;
  cam.max_depth         = 50;

  cam.vfov     = 25;
  cam.lookfrom = point3(12,1.5,5);
  cam.lookat   = point3(0,0.5,0);
  cam.vup      = vec3(0,1,0.1);

  cam.defocus_angle = 0.6;
  cam.focus_dist    = 10.0;

  cam.render(world);
}
