#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"

#include "hittable.h"

class camera {
  public:
    double aspect_ratio = 1.0; // Ratio of image width over height
    int image_width = 100; // Rendered image width in pixel count
    int samples_per_pixel = 10; // Count of random samples for each pixel
    int max_depth = 10; // Maximum number of ray bounces into scene
    float max_intersection_dist = infinity;
    float min_intersection_dist = 0.001; // This is a small value to prevent shadow acne

    void render(const hittable& world) {
      initialize();

      std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

      for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for (int i = 0; i < image_width; i++) {
          color pixel_color(0, 0, 0);
          for (int k = 0; k < samples_per_pixel; k++) {
            ray r = get_ray(i, j);
            pixel_color += ray_color(r, max_depth, world);
          }
          pixel_color /= samples_per_pixel;
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

    ray get_ray(int i, int j) const {
      // Construct a camera ray originating from the origin and directed at randomly sampled
      // point around the pixel location i, j.

      auto offset = sample_disk();
      auto pixel_sample = pixel00_loc
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

      auto ray_origin = camera_center;
      auto ray_direction = pixel_sample - ray_origin;

      return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
      // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
      return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    vec3 sample_disk() const {
      // Returns the vector to a random point in the unit disk.
      // Believe it or not, this is a more efficient way to generate a random point in the unit disk than using polar coordinates.
      vec3 rand = random_in_unit_sphere();
      return vec3(rand.x(), rand.y(), 0);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
      // If we've exceeded the ray bounce limit, no more light is gathered.
      if (depth <= 0) return color(0,0,0);

      hit_record rec;
      if (world.hit(r, interval(min_intersection_dist, max_intersection_dist), rec)) {
        vec3 direction = rec.normal + random_unit_vector();
        return 0.5 * ray_color(ray(rec.p,  direction), depth - 1, world);
      }

      vec3 unit_direction = normalize(r.direction());
      auto a = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - a) * ground_color + a * sky_color;
    }
};

#endif
