#ifndef MAT4_H
#define MAT4_H

#include "vec3.h"

const int SIZE = 4;

class mat4 {
  public:
    mat4() {
      e[0 + SIZE * 0] = 1;
      e[1 + SIZE * 0] = 0;
      e[2 + SIZE * 0] = 0;
      e[3 + SIZE * 0] = 0;
      e[0 + SIZE * 1] = 0;
      e[1 + SIZE * 1] = 1;
      e[2 + SIZE * 1] = 0;
      e[3 + SIZE * 1] = 0;
      e[0 + SIZE * 2] = 0;
      e[1 + SIZE * 2] = 0;
      e[2 + SIZE * 2] = 1;
      e[3 + SIZE * 2] = 0;
      e[0 + SIZE * 3] = 0;
      e[1 + SIZE * 3] = 0;
      e[2 + SIZE * 3] = 0;
      e[3 + SIZE * 3] = 1;
    }

    mat4(double e00, double e01, double e02, double e03,
         double e10, double e11, double e12, double e13,
         double e20, double e21, double e22, double e23,
         double e30, double e31, double e32, double e33) {
      e[0 + SIZE * 0] = e00;
      e[1 + SIZE * 0] = e01;
      e[2 + SIZE * 0] = e02;
      e[3 + SIZE * 0] = e03;
      e[0 + SIZE * 1] = e10;
      e[1 + SIZE * 1] = e11;
      e[2 + SIZE * 1] = e12;
      e[3 + SIZE * 1] = e13;
      e[0 + SIZE * 2] = e20;
      e[1 + SIZE * 2] = e21;
      e[2 + SIZE * 2] = e22;
      e[3 + SIZE * 2] = e23;
      e[0 + SIZE * 3] = e30;
      e[1 + SIZE * 3] = e31;
      e[2 + SIZE * 3] = e32;
      e[3 + SIZE * 3] = e33;
    }

    static mat4 translate(const vec3& t) {
      return mat4(1, 0, 0, t.x(),
                  0, 1, 0, t.y(),
                  0, 0, 1, t.z(),
                  0, 0, 0, 1);
    }

    // Add operator to access i,j element of matrix
    double operator()(int i, int j) const { return e[i + SIZE * j]; }

    // Add operator to update i,j element of matrix
    // double& operator()(int i, int j) { return e[i + SIZE * j]; }

    void set(int i, int j, double val) { e[i + SIZE * j] = val; }

    /*
    0  1  2  3
    4  5  6  7
    8  9  10 11
    12 13 14 15
    */
    double determinant() {
      // return 
    }

    mat4 transponse() {
      mat4 result;
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
          result.set(i, j, e[j + SIZE * i]);
        }
      }
      return result;
    }

    mat4 invert() {
      double det;
      mat4 cofactor;

      // det = 
    }

  private:
    double e[16];
};

inline vec3 operator*(const mat4& m, const vec3& v) {
  return vec3(m(0,0) * v.x() + m(0,1) * v.y() + m(0,2) * v.z() + m(0,3) * 1,
              m(1,0) * v.x() + m(1,1) * v.y() + m(1,2) * v.z() + m(1,3) * 1,
              m(2,0) * v.x() + m(2,1) * v.y() + m(2,2) * v.z() + m(2,3) * 1);
}

inline mat4 operator*(const mat4& m, const mat4& n) {
  mat4 result;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      double sum = 0;
      for (int k = 0; k < SIZE; k++) {
        sum += m(i,k) * n(k,j);
      }
      result.set(i, j, sum);
    }
  }
  return result;
  // return mat4(m(0,0) * n(0,0) + m(0,1) * n(1,0) + m(0,2) * n(2,0) + m(0,3) * n(3,0),
  //             m(0,0) * n(0,1) + m(0,1) * n(1,1) + m(0,2) * n(2,1) + m(0,3) * n(3,1),
  //             m(0,0) * n(0,2) + m(0,1) * n(1,2) + m(0,2) * n(2,2) + m(0,3) * n(3,2),
  //             m(0,0) * n(0,3) + m(0,1) * n(1,3) + m(0,2) * n(2,3) + m(0,3) * n(3,3),
  //             m(1,0) * n(0,0) + m(1,1) * n(1,0) + m(1,2) * n(2,0) + m(1,3) * n(3,0),
  //             m(1,0) * n(0,1) + m(1,1) * n(1,1) + m(1,2) * n(2,1) + m(1,3) * n(3,1),
  //             m(1,0) * n(0,2) + m(1,1) * n(1,2) + m(1,2) * n(2,2) + m(1,3) * n(3,2),
  //             m(1,0) * n(0,3) + m(1,1) * n(1,3) + m(1,2) * n(2,3) + m(1,3) * n(3,3),
  //             m(2,0) * n(0,0) + m(2,1) * n(1,0) + m(2,2) * n(2,0) + m(2,3) * n(3,0),
  //             m(2,0) * n(0,1) + m(2,1) * n(1,1) + m(2,2) * n(2,1) + m(2,3) * n(3,1),
  //             m(2,0) * n(0,2) + m(2,1) * n(1,2) + m(2,2) * n(2,2) + m(2,3) * n(3,2),
  //             m(2,0) * n(0,3) + m(2,1) * n(1,3) + m(2,2) * n(2,3) + m(2,3) * n(3,3),
  //             m(3,0) * n(0,0) + m(3,1) * n(1,0) + m(3,2) * n(2,0) + m(3,3) * n(3,0),
  //             m(3,0) * n(0,1) + m(3,1) * n(1,1) + m(3,2) * n(2,1) + m(3,3) * n(3,1),
  //             m(3,0) * n(0,2) + m(3,1) * n(1,2) + m(3,2) * n(2,2) + m(3,3) * n(3,2),
  //             m(3,0) * n(0,3) + m(3,1) * n(1,3) + m(3,2) * n(2,3) + m(3,3) * n(3,3));
}

inline mat4 operator*(const double t, const mat4& m) {
  mat4 result;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      result.set(i, j, t * m(i,j));
    }
  }
  return result;
  // return mat4(t * m(0,0), t * m(0,1), t * m(0,2), t * m(0,3),
  //             t * m(1,0), t * m(1,1), t * m(1,2), t * m(1,3),
  //             t * m(2,0), t * m(2,1), t * m(2,2), t * m(2,3),
  //             t * m(3,0), t * m(3,1), t * m(3,2), t * m(3,3));
}

inline mat4 operator*(const mat4& m, const double t) {
  return t * m;
}

inline mat4 operator/(const mat4& m, const double t) {
  return (1/t) * m;
}

inline mat4 operator+(const mat4& m, const mat4& n) {
  return mat4(m(0,0) + n(0,0), m(0,1) + n(0,1), m(0,2) + n(0,2), m(0,3) + n(0,3),
              m(1,0) + n(1,0), m(1,1) + n(1,1), m(1,2) + n(1,2), m(1,3) + n(1,3),
              m(2,0) + n(2,0), m(2,1) + n(2,1), m(2,2) + n(2,2), m(2,3) + n(2,3),
              m(3,0) + n(3,0), m(3,1) + n(3,1), m(3,2) + n(3,2), m(3,3) + n(3,3));
}

inline mat4 operator-(const mat4& m, const mat4& n) {
  return m + (-1 * n);
}

#endif
