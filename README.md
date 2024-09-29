# Particle System in C++

This project provides a framework for building and visualizing particle systems using C++ with VTK file generation. The resulting VTK files can be visualized using ParaView for an intuitive, graphical representation of the particle simulations.

## Features

- **Particle Simulation**: The system supports customizable particle interactions and simulations.
- **Visualization**: Output is saved in VTK format, which can be viewed in ParaView, a popular open-source visualization application.
- **Testing**: Includes a suite of 11 tests, both unit and system tests, to ensure the accuracy and stability of the particle system.

## How to Use

### Build Instructions

To compile the project, follow these steps:

```sh
mkdir build
cd build
cmake ..
make
```

This will generate the necessary executables for running the particle system and its tests.

## Running Tests

The project includes 11 tests located in the `test` directory. These tests include both Google Tests (GTests) and regular tests to validate different aspects of the particle system.

- **Google Tests**: Test files follow the naming convention `*_test.cxx`.
- **Regular Tests**: Non-GTest files that test specific simulation features.

To compile and run a specific test:

```sh
make <name_of_the_test>
./test/<name_of_the_test>
```

## Generating Documentation

Documentation for the project is automatically generated using Doxygen. To generate documentation locally:

```sh
cd doc
doxygen doxyfilerc
```

Alternatively, pre-generated documentation can be found in the `docu` directory.

## Visualization with ParaView

After running the simulations, the VTK output files can be visualized using ParaView. Simply load the generated VTK files into ParaView for a detailed view of the particle interactions.

## Directory Structure

- **src/**: Contains the source code for the particle system.
- **test/**: Contains all the test files, including Google Tests and custom tests.
- **doc/**: Contains the Doxygen configuration file and scripts for generating documentation.
- **docu/**: Pre-generated documentation.
- **build/**: The directory where compiled binaries and objects will be stored.

