#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"

#include "primitives/hittable.h"
#include "material.h"

class camera {
  public:
    double aspect_ratio = 1.0; // Ratio of image width over height
    int image_width = 100; // Rendered image width in pixel count
    int samples_per_pixel = 10; // Count of random samples for each pixel
    int max_depth = 10; // Maximum number of ray bounces into scene
    double max_intersection_dist = infinity;
    double min_intersection_dist = 0.001; // This is a small value to prevent shadow acne
    color sky_color = color(0.3, 0.5, 1.0);
    color ground_color = color(1.0, 1.0, 1.0);

    double vfov = 90; // Vertical view angle (field of view)
    point3 lookfrom = point3(0,0,0); // Point camera is looking from
    point3 lookat = point3(0,0,-1); // Point camera is looking at
    vec3 vup = vec3(0,1,0); // Camera-relative "up" direction

    double defocus_angle = 0; // Variation angle of rays through each pixel
    double focus_dist = 10; // Distance from camera lookfrom point to plane of perfect focus

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

    point3 camera_center;
    point3 pixel00_loc;

    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u, v, w; // Camera frame basis vectors
    vec3 defocus_disk_u; // Defocus disk horizontal radius
    vec3 defocus_disk_v; // Defocus disk vertical radius

    void initialize() {
      image_height = int(image_width / aspect_ratio);
      image_height = (image_height < 1) ? 1 : image_height;

      camera_center = lookfrom;

      // Determine viewport dimensions.
      auto theta = degrees_to_radians(vfov);
      auto h = std::tan(theta/2);
      auto viewport_height = 2 * h * focus_dist;
      double viewport_width = viewport_height * (double(image_width)/image_height);

      // Calculate the u,v,w unit basis vectors for the camera coordinate frame.
      w = unit_vector(lookfrom - lookat);
      u = unit_vector(cross(vup, w));
      v = cross(w, u);

      // Calculate the vectors across the horizontal and down the vertical viewport edges.
      vec3 viewport_u = viewport_width * u;    // Vector across viewport horizontal edge
      vec3 viewport_v = viewport_height * -v;  // Vector down viewport vertical edge

      // Calculate the horizontal and vertical delta vectors from pixel to pixel.
      pixel_delta_u = viewport_u / image_width;
      pixel_delta_v = viewport_v / image_height;

      // Calculate the location of the upper left pixel.
      vec3 viewport_upper_left = camera_center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
      pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

      // Calculate the camera defocus disk basis vectors.
      double defocus_radius = focus_dist * std::tan(degrees_to_radians(defocus_angle / 2));
      defocus_disk_u = u * defocus_radius;
      defocus_disk_v = v * defocus_radius;
    }

    ray get_ray(int i, int j) const {
      // Construct a camera ray originating from the defocus disk and directed at a randomly
      // sampled point around the pixel location i, j.

      auto offset = sample_disk();
      auto pixel_sample = pixel00_loc
        + ((i + offset.x()) * pixel_delta_u)
        + ((j + offset.y()) * pixel_delta_v);

      auto ray_origin = (defocus_angle <= 0) ? camera_center : defocus_disk_sample();
      auto ray_direction = pixel_sample - ray_origin;
      auto ray_time = random_double();

      return ray(ray_origin, ray_direction, ray_time);
    }

    vec3 sample_square() const {
      // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
      return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    vec3 sample_disk() const {
      // Returns the vector to a random point in the unit disk.
      return random_in_unit_disk();
    }

    point3 defocus_disk_sample() const {
      // Returns a random point in the camera defocus disk.
      auto p = random_in_unit_disk();
      return camera_center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
    }

    color ray_color(const ray& r, int depth, const hittable& world) const {
      // If we've exceeded the ray bounce limit, no more light is gathered.
      if (depth <= 0) return color(0,0,0);

      hit_record rec;
      
      // If the ray hits nothing, return the background color.
      if (!world.hit(r, interval(min_intersection_dist, max_intersection_dist), rec)) {
        vec3 unit_direction = normalize(r.direction());
        auto a = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - a) * ground_color + a * sky_color;
      }

      ray scattered_ray;
      color attenuation_color;
      color color_from_emission = rec.mat->emitted(rec.u, rec.v, rec.p);

      if (!rec.mat->scatter(r, rec, attenuation_color, scattered_ray))
        return color_from_emission;

      color color_from_scatter = attenuation_color * ray_color(scattered_ray, depth - 1, world);

      return color_from_emission + color_from_scatter;
    }
};

#endif
