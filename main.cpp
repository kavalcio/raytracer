#include <iostream>

#include "vec3.h"

int main() {

  // Image

  int image_width = 256;
  int image_height = 256;

  // Render

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; i++) {
      auto r = double(i) / (image_width-1);
      auto g = double(j) / (image_height-1);
      auto b = 0.0;

      vec3 my_color = vec3(r, g, b);

      int ir = int(255.999 * my_color.r());
      int ig = int(255.999 * my_color.g());
      int ib = int(255.999 * my_color.b());

      std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }

  std::clog << "\rDone.                 \n";
}
