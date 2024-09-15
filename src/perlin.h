#ifndef PERLIN_H
#define PERLIN_H

#include "main.h"

#include <vector>

// TODO: add octaves
class perlin {
  public:
    perlin() {
      // Initialize the permutation vector with random values in the range [0,255].
      for (int i = 0; i < point_count; i++) {
        perm_x[i] = i;
        perm_y[i] = i;
        perm_z[i] = i;
        randvec[i] = random_unit_vector();
      }

      permute();
    }

    double noise(const point3& p) const {
      auto u = p.x() - std::floor(p.x());
      auto v = p.y() - std::floor(p.y());
      auto w = p.z() - std::floor(p.z());

      auto i = int(std::floor(p.x()));
      auto j = int(std::floor(p.y()));
      auto k = int(std::floor(p.z()));

      vec3 corners[2][2][2];

      for (int di = 0; di < 2; di++) {
        for (int dj = 0; dj < 2; dj++) {
          for (int dk = 0; dk < 2; dk++) {
            corners[di][dj][dk] = randvec[
              perm_x[(i+di) & (point_count - 1)] ^
              perm_y[(j+dj) & (point_count - 1)] ^
              perm_z[(k+dk) & (point_count - 1)]
            ];
          }
        }
      }

      return interpolate(corners, u, v, w);
    }

  private:
    static const int point_count = 256;
    vec3 randvec[point_count];
    int perm_x[point_count];
    int perm_y[point_count];
    int perm_z[point_count];

    void permute() {
      for (int i = point_count - 1; i > 0; i--) {
        int target_x = random_int(0, i);
        int target_y = random_int(0, i);
        int target_z = random_int(0, i);
        std::swap(perm_x[i], perm_x[target_x]);
        std::swap(perm_y[i], perm_y[target_y]);
        std::swap(perm_z[i], perm_z[target_z]);
      }
    }

    static double interpolate(const vec3 corners[2][2][2], double u, double v, double w) {
      auto uu = u * u * (3 - 2 * u);
      auto vv = v * v * (3 - 2 * v);
      auto ww = w * w * (3 - 2 * w);
      auto accum = 0.0;

      for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
          for (int k = 0; k < 2; k++) {
            vec3 weight_v(u - i, v - j, w - k);
            accum += (i * uu + (1 - i) * (1 - uu))
              * (j * vv + (1 - j) * (1 - vv))
              * (k * ww + (1 - k) * (1 - ww))
              * dot(corners[i][j][k], weight_v);
          }
        }
      }

      return accum;
    }
};

#endif
