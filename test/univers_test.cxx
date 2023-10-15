#include <gtest/gtest.h>
#include "Univers.hxx"
#include "../include/Particle.hxx"
#include "../include/Vecteur.hxx"


TEST(UniversTest, Constructor1) {
    //Create a 3D universe with 10 particles
    int dim = 3;
    int nb_particles = 10;

    Univers univers(dim, nb_particles);

    EXPECT_EQ(univers.getParticles().size(), nb_particles);
}

TEST(UniversTest, UniversConstructor2) {
    // Create a 2D Univers
    int nb_particules = 2;
    double vecteur[2] = {10.0, 10.0};
    Vecteur Ld(2, vecteur);
    double radius = 2.0;
    double position[2] = {1.0, 2.0};
    double velocity[2] = {4.0, 5.0};
    std::vector<std::shared_ptr<Particle>> particules;
    std::shared_ptr<Particle> particle = std::make_shared<Particle>(2, position, velocity, 1.0, "A");
    std::shared_ptr<Particle> particle1 = std::make_shared<Particle>(2, position, velocity, 1.0, "B");
    particules.push_back(particle);
    particules.push_back(particle1);
    Univers univers2d(2, nb_particules, particules, Ld, radius, 0);

    // Check that the evolution of the mesh is correct
    double forceVector[2] = {7.0, 8.0};
    double forceVector1[2] = {10.0, 11.0};
    Vecteur force(2, forceVector);
    Vecteur force1(2, forceVector1);
    particle->setForce(force);
    particle1->setForce(force1);
    univers2d.compute_all_forces();
    EXPECT_FALSE(particle->getForce()[0] == 7.0);
    EXPECT_FALSE(particle->getForce()[1] == 8.0);
    EXPECT_FALSE(particle1->getForce()[0] == 10.0);
    EXPECT_FALSE(particle1->getForce()[1] == 11.0);
}



TEST(UniversTest, UniversConstructor3) {
    // Create a 2D Univers
    int nb_particules = 3;
    double vecteur[3] = {10.0, 10.0, 10.0};
    Vecteur Ld(3, vecteur);
    double radius = 2.0;
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    std::vector<std::shared_ptr<Particle>> particules;
    std::shared_ptr<Particle> particle = std::make_shared<Particle>(3, position, velocity, 1.0, "A");
    std::shared_ptr<Particle> particle1 = std::make_shared<Particle>(3, position, velocity, 1.0, "B");
    std::shared_ptr<Particle> particle2 = std::make_shared<Particle>(3, position, velocity, 1.0, "C");
    particules.push_back(particle);
    particules.push_back(particle1);
    particules.push_back(particle2);
    Univers univers3d(3, nb_particules, particules, Ld, radius, 0);

    // Check that the evolution of the mesh is correct
    double forceVector[3] = {7.0, 8.0, 9.0};
    double forceVector1[3] = {10.0, 11.0, 12.0};
    double forceVector2[3] = {13.0, 14.0, 15.0};
    Vecteur force(3, forceVector);
    Vecteur force1(3, forceVector1);
    Vecteur force2(3, forceVector2);
    particle->setForce(force);
    particle1->setForce(force1);
    particle2->setForce(force2);
    univers3d.compute_all_forces();
    EXPECT_FALSE(particle->getForce()[0] == 7.0);
    EXPECT_FALSE(particle->getForce()[1] == 8.0);
    EXPECT_FALSE(particle->getForce()[2] == 9.0);
    EXPECT_FALSE(particle1->getForce()[0] == 10.0);
    EXPECT_FALSE(particle1->getForce()[1] == 11.0);
    EXPECT_FALSE(particle1->getForce()[2] == 12.0);
    EXPECT_FALSE(particle2->getForce()[0] == 13.0);
    EXPECT_FALSE(particle2->getForce()[1] == 14.0);
    EXPECT_FALSE(particle2->getForce()[2] == 15.0);
}   






