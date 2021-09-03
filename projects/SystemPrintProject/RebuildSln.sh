rm -rf build
mkdir build
cd build/
cmake ..
make
cd ..
g++ main.cpp -o main
