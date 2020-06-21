## Logit Normal Mixed Model

### Usage

Modify "main.cpp" as you want and excute the commands below.

```console
$ make
$ ./main
```

In Makefile,

```Makefile
main: main.o models.o utils.o
	g++ -Wall -o main main.o models.o utils.o
utils.o: utils.cpp
	g++ -Wall -c utils.cpp
models.o: models.cpp
	g++ -Wall -c models.cpp
main.o: main.cpp
	g++ -Wall -c main.cpp

clean:
	rm -f *.o main
```

### Python-bind

```console
$ sh make_python_module.sh
```

where make_python_module.sh is

```Shell
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
```
