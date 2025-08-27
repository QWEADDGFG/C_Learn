# chmod +x run.sh
mkdir build
cd build
cmake ..
make
cp ../bin/demo ..
# cp ../bin/grade_converter ..