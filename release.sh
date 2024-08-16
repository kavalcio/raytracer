cmake -B build/Release -DCMAKE_BUILD_TYPE=Release
cmake --build build/Release
./build/Release/main > ./output/image_release.ppm
