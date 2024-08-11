#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"

#include "hittable.h"

class camera {
  public:
    double aspect_ratio = 1.0; // Ratio of image width over height
    int image_width = 100; // Rendered image width in pixel count

    void render(const hittable& world) {
      initialize();

      std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

      for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
          auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
          auto ray_direction = pixel_center - camera_center;
          ray r(camera_center, ray_direction);

          color pixel_color = ray_color(r, world);

          write_color(std::cout, pixel_color);
        }
      }

      std::clog << "\rDone.                 \n";
    }

  private:
    int image_height;

    color sky_color = color(0.5, 0.7, 1.0);
    color ground_color = color(1.0, 1.0, 1.0);

    double focal_length;
    double viewport_height;
    double viewport_width;
    point3 camera_center;

    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 viewport_upper_left;
    vec3 pixel00_loc;

    void initialize() {
      camera_center = point3(0, 0, 0);
      image_height = int(image_width / aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;

      // Determine viewport dimensions.
      focal_length = 1.0;
      viewport_height = 2.0;
      viewport_width = viewport_height * (double(image_width)/image_height);

      // Calculate the vectors across the horizontal and down the vertical viewport edges.
      vec3 viewport_u = vec3(viewport_width, 0, 0);
      vec3 viewport_v = vec3(0, -viewport_height, 0);

      // Calculate the horizontal and vertical delta vectors from pixel to pixel.
      pixel_delta_u = viewport_u / image_width;
      pixel_delta_v = viewport_v / image_height;

      // Calculate the location of the upper left pixel.
      viewport_upper_left = camera_center
        - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
      pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    color ray_color(const ray& r, const hittable& world) const {
      hit_record rec;
      if (world.hit(r, interval(0, infinity), rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
      }

      vec3 unit_direction = normalize(r.direction());
      auto a = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - a) * sky_color + a * ground_color;
    }
};

#endif
