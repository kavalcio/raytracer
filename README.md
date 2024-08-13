```shell
# Quickly compile and run code for test purposes
$ sh ./debug.sh

# Configure and build release binaries under `build/Release`
$ cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
$ cmake --build build/Release

# Configure and build debug binaries under `build/Debug`
$ cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
$ cmake --build build/Debug
```

Based on [_Ray Tracing in One Weekend_](https://raytracing.github.io/books/RayTracingInOneWeekend.html).
