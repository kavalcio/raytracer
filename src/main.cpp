#include "main.h"
#include "sphere.h"

color sky_color = color(0.5, 0.7, 1.0);
color ground_color = color(1.0, 1.0, 1.0);

color ray_color(const ray& r) {
  sphere sphere_1 = sphere(point3(0, 0, -1), 0.5);
  hit_record rec;
  if (sphere_1.hit(r, 0, 1000, rec)) {
    return 0.5 * (rec.normal + color(1, 1, 1));
  }

  vec3 unit_direction = normalize(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * sky_color + a * ground_color;
}

int main() {

  // Image

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;

  // Calculate the image height, and ensure that it's at least 1.
  int image_height = int(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  // Camera

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height * (double(image_width)/image_height);
  vec3 camera_center = point3(0, 0, 0);

  // Calculate the vectors across the horizontal and down the vertical viewport edges.
  vec3 viewport_u = vec3(viewport_width, 0, 0);
  vec3 viewport_v = vec3(0, -viewport_height, 0);

  // Calculate the horizontal and vertical delta vectors from pixel to pixel.
  vec3 pixel_delta_u = viewport_u / image_width;
  vec3 pixel_delta_v = viewport_v / image_height;

  // Calculate the location of the upper left pixel.
  vec3 viewport_upper_left = camera_center
                            - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
  vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
      auto ray_direction = pixel_center - camera_center;
      ray r(camera_center, ray_direction);

      color pixel_color = ray_color(r);

      // color pixel_color = color(double(i) / (image_width-1), double(j) / (image_height-1), 0.0);
      write_color(std::cout, pixel_color);
    }
  }

  std::clog << "\rDone.                 \n";
}
