#ifndef TEXTURE_H
#define TEXTURE_H

#include "main.h"
#include "image_loader.h"
#include "perlin.h"

class texture {
  public:
    virtual ~texture() = default;

    virtual color value(double u, double v, const point3& p) const = 0;
};

class solid_color : public texture {
  public:
    solid_color(const color& albedo) : albedo(albedo) {}

    solid_color(double r, double g, double b) : solid_color(color(r, g, b)) {}

    color value(double u, double v, const point3& p) const override {
      return albedo;
    }

  private:
    color albedo;
};

class checker_texture : public texture {
  public:
    checker_texture(double scale, shared_ptr<texture> even, shared_ptr<texture> odd)
      : inv_scale(1.0 / scale), even(even), odd(odd) {}

    checker_texture(double scale, const color& c1, const color& c2)
      : checker_texture(scale, make_shared<solid_color>(c1), make_shared<solid_color>(c2)) {}

    color value(double u, double v, const point3& p) const override {
      auto uInteger = int(std::floor(u * inv_scale));
      auto vInteger = int(std::floor(v * inv_scale));

      bool isEven = (uInteger + vInteger) % 2 == 0;

      return isEven ? even->value(u, v, p) : odd->value(u, v, p);
    }

  private:
    double inv_scale;
    shared_ptr<texture> even;
    shared_ptr<texture> odd;
};

class image_texture : public texture {
  public:
    image_texture(const char* filename) : image(filename) {}

    color value(double u, double v, const point3& p) const override {
      // If we have no texture data, then return solid cyan as a debugging aid.
      if (image.height() <= 0) return color(0,1,1);

      // Clamp input texture coordinates to [0,1] x [1,0]
      u = interval(0,1).clamp(u);
      v = 1.0 - interval(0,1).clamp(v);  // Flip V to image coordinates

      auto i = int(u * image.width());
      auto j = int(v * image.height());
      auto pixel = image.pixel_data(i, j);

      auto color_scale = 1.0 / 255.0;
      return color(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
    }

  private:
    image_loader image;
};

class noise_texture : public texture {
  public:
    noise_texture(double scale, int depth) : scale(scale), depth(depth) {}
    
    color value(double u, double v, const point3& p) const override {
      return color(1, 1, 1) * 0.5 * (1 + noise.compounded_noise(scale * p, depth));
    }
  
  private:
    perlin noise;
    double scale;
    int depth;

};

class marble_texture : public texture {
  public:
    marble_texture(double scale, int depth) : scale(scale), depth(depth) {}

    color value(double u, double v, const point3& p) const override {
      return color(1, 1, 1) * 0.5 * (1 + std::sin(scale * p.z() + 10 * std::fabs(noise.compounded_noise(p, depth))));
    }

  private:
    perlin noise;
    double scale;
    int depth;
};

#endif
