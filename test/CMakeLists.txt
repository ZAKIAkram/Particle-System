find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

# Create the executable
add_executable(testVec testVec.cxx)
add_executable(testParticles testParticles.cxx)
add_executable(testGalaxy testGalaxy.cxx)
add_executable(testUnivers testUnivers.cxx)
add_executable(testCells testCells.cxx )
add_executable(testCollisions testCollision.cxx)
add_executable(testStormerVerlet testStormerVerlet.cxx)


#Link libraries
target_link_libraries(testStormerVerlet univers particle vecteur cell)
target_link_libraries(testCollisions univers particle vecteur cell)
target_link_libraries(testCells univers particle vecteur cell)
target_link_libraries(testUnivers univers particle vecteur cell)
target_link_libraries(testGalaxy univers particle vecteur cell)
target_link_libraries(testParticles univers particle vecteur cell)
target_link_libraries(testVec univers particle vecteur cell)





# For each test (test suite), an executable is created
add_executable(particle_test ../test/particle_test.cxx)
add_executable(univers_test ../test/univers_test.cxx)
add_executable(cellule_test ../test/cellule_test.cxx)
add_executable(vecteur_test ../test/vecteur_test.cxx)


## Don't forget to add the project libraries (UniversLib, ParticleLib, VecteurLib)
target_link_libraries(particle_test univers particle vecteur cell ${GTEST_BOTH_LIBRARIES})
target_link_libraries(univers_test univers particle vecteur cell ${GTEST_BOTH_LIBRARIES})
target_link_libraries(cellule_test univers particle vecteur cell ${GTEST_BOTH_LIBRARIES})
target_link_libraries(vecteur_test univers particle vecteur cell ${GTEST_BOTH_LIBRARIES})


include(GoogleTest)
gtest_discover_tests(particle_test)
gtest_discover_tests(univers_test)
gtest_discover_tests(cellule_test)
gtest_discover_tests(vecteur_test)

