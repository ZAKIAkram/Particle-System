# Particle System in C++
This project allows you to build and visualize particle systems using C++ and VTK files that can be visualied in Paraview
## Usage :
```sh
mkdir build
cd build
cmake ..
```

There are 11 tests in the 'test' directory. To run a test, you can use the command :
```sh
make <name_of_the_test>
./test/<name_of_the_test>
```

Among the 11 tests, there are 'google_tests,' and the names of GTests follow the format: <test_name>_test.cxx. 
The other tests are regular tests. 
The testCollision.cxx in the 'test' directory is the test that simulates lab 4, but it takes some time.

To generate the documentation, you can use the command:
```sh
cd doc
doxygen doxyfilerc
```
There is already a generated documentation in the 'docu' directory
