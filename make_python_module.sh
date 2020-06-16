if [ ! -d ./pybind11 ]; then
    git clone https://github.com/pybind/pybind11.git
fi

if [ ! -d ./build ]; then
    mkdir build
fi

cd build
cmake ..
make
mv *.so ../