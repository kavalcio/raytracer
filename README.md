# Ray Tracer
![cover image](https://github.com/kavalcio/raytracing/cover.jpg?raw=true)

A minimal ray tracing renderer, written in C++.

Based on Peter Shirley's [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html).

## Building and Running
More detailed run instructions on the [course page](https://github.com/RayTracing/raytracing.github.io).
```shell
# Configure and build release binaries under `build/Release`
$ cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
$ cmake --build build/Release
$ ./build/Release/main > ./output/image_release.ppm

# Configure and build debug binaries under `build/Debug`
$ cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build/Debug
$ ./build/Debug/main > ./output/image_debug.ppm
```
