cmake_minimum_required (VERSION 3.16.3)
project(Demo CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -g")
# Commentaire
# Add the include directory
include_directories(include)



add_subdirectory(src)
add_subdirectory(test)

