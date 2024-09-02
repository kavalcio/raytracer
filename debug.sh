set -e
cmake -B build/Debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build/Debug
mkdir -p output
./build/Debug/main > ./output/image_debug.ppm
