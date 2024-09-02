set -e
cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release
mkdir -p output
./build/Release/main > ./output/image_release.ppm
