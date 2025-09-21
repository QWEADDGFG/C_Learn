# chmod +x run.sh
# mkdir build
cd build
cmake ..
make clean
make -j4
# cp ../bin/demo ..