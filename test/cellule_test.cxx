
#include <gtest/gtest.h>
#include "../include/Cell.hxx"
#include "../include/Particle.hxx"

Cell cell;
// Test case for inserting a particle into the cell
TEST(CellTest, InsertParticle) {
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    Particle particle(3, position, velocity, 0.1, "A");
    cell.insert_particle(std::make_shared<Particle>(particle));


    // Check if the number of particles in the cell has increased by 1
    EXPECT_EQ(cell.getNbParticles(), 1);
}

TEST(CellTest, RemoveParticle) {
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    Particle particle(3, position, velocity, 0.1, "A");
    cell.insert_particle(std::make_shared<Particle>(particle));
    cell.remove_particle(std::make_shared<Particle>(particle));

    // Check if the number of particles in the cell has decreased by 1
    EXPECT_EQ(cell.getNbParticles(), 1);
}


// Test case for getting the particles in the cell
TEST(CellTest, GetParticles) {
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    Particle particle(3, position, velocity, 0.1, "A");
    Particle particle1(3, position, velocity, 0.1, "B");
    cell.insert_particle(std::make_shared<Particle>(particle));
    cell.insert_particle(std::make_shared<Particle>(particle1));

    auto& particles = cell.getParticles();

    // Check if the number of particles in the cell is correct
    EXPECT_EQ(cell.getNbParticles(), 3);
}

