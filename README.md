# Ray Tracer
![cover image](https://github.com/kavalcio/raytracer/blob/main/cover.jpg?raw=true)

A minimal ray tracing renderer, written in C++.

Based on Peter Shirley's [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

## Building and Running
More detailed instructions on the [course page](https://github.com/RayTracing/raytracing.github.io).
```shell
# Build and run renderer in release mode
$ cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
$ cmake --build build/Release
$ ./build/Release/main > ./output/image_release.ppm

# Build and run renderer in debug mode
$ cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build/Debug
$ ./build/Debug/main > ./output/image_debug.ppm
```
