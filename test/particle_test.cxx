#include <gtest/gtest.h>
#include <iostream>
#include "../include/Particle.hxx"
#include "../include/Vecteur.hxx"

TEST(ParticleTest, PartTest) {
// Test Particle constructor with dimension, position, velocity, mass, category parameters  
  double position[3] = {1.0, 2.0, 3.0};
  double velocity[3] = {4.0, 5.0, 6.0};
  Particle particle1(3, position, velocity, 0.1, "A");
  EXPECT_DOUBLE_EQ(particle1.getMasse(), 0.1);
  EXPECT_EQ(particle1.getId(), 0);
  EXPECT_EQ(particle1.getPosition().getDim(), 3);
  EXPECT_EQ(particle1.getForce().getDim(), 3);
  EXPECT_EQ(particle1.getOldForce().getDim(), 3);
  EXPECT_EQ(particle1.getPosition().getDim(), 3);
}

TEST(ParticleTest, ParticlePosition) {
  double position[3] = {1.0, 2.0, 3.0};
  double velocity[3] = {4.0, 5.0, 6.0};
  Particle particle1(3, position, velocity, 0.1, "A");
  EXPECT_DOUBLE_EQ(particle1.getPosition()[0], 1.0);
  EXPECT_DOUBLE_EQ(particle1.getPosition()[1], 2.0);
  EXPECT_DOUBLE_EQ(particle1.getPosition()[2], 3.0);
}

TEST(ParticuleTest, SetForce) {
    // Create a Particule object
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    double masse = 1.0;
    Particle particule(3, position, velocity, masse, "B");

    // Set a new force
    double vecteur[3] = {7.0, 8.0, 9.0};
    Vecteur force(3, vecteur);
    particule.setForce(force);

    // Check that the force is set correctly
    ASSERT_EQ(particule.getForce()[0], force[0]);
    ASSERT_EQ(particule.getForce()[1], force[1]);
    ASSERT_EQ(particule.getForce()[2], force[2]);
}

TEST(ParticuleTest, SetOldForce) {
    // Create a Particule object
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    double masse = 1.0;
    Particle particule(3, position, velocity, masse, "C");

    // Set a new old force
    double vecteur[3] = {7.0, 8.0, 9.0};
    Vecteur Oldforce(3, vecteur);
    particule.setOldForce(Oldforce);

    // Check that the force is set correctly
    ASSERT_EQ(particule.getOldForce()[0], Oldforce[0]);
    ASSERT_EQ(particule.getOldForce()[1], Oldforce[1]);
    ASSERT_EQ(particule.getOldForce()[2], Oldforce[2]);
}

TEST(ParticuleTest, SetVitesse) {
    // Create a Particule object
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    double masse = 1.0;
    Particle particule(3, position, velocity, masse, "D");

    // Check that the force is set correctly
    ASSERT_EQ(particule.getVitesse()[0], velocity[0]);
    ASSERT_EQ(particule.getVitesse()[1], velocity[1]);
    ASSERT_EQ(particule.getVitesse()[2], velocity[2]);
}

TEST(ParticleTest, UpdatePosition) {
    
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    double masse = 1.0;
    // Create a Particle object
    Particle particle(3 , position , velocity , 1.0, "E");

    // Set the force and other necessary properties
    double vecteur[3] = {7.0, 8.0, 9.0};
    Vecteur force(3, vecteur);
    particle.setForce(force);
    // Call the update_position method with a specific time step (dt)
    particle.update_position(0.1);
    // Check that the position is updated correctly
    ASSERT_EQ(particle.getPosition()[0], 1.435);
    ASSERT_EQ(particle.getPosition()[1], 2.54);
    ASSERT_EQ(particle.getPosition()[2], 3.645);
}

TEST(ParticleTest, UpdateVitesse) {
    
    double position[3] = {1.0, 2.0, 3.0};
    double velocity[3] = {4.0, 5.0, 6.0};
    double masse = 1.0;
    // Create a Particle object
    Particle particle(3 , position , velocity , 1.0, "E");

    // Set the force and other necessary properties
    double vecteur[3] = {7.0, 8.0, 9.0};
    Vecteur force(3, vecteur);
    particle.setForce(force);
    particle.setOldForce(force);
    // Call the update_position method with a specific time step (dt)
    particle.update_vitesse(0.1);
    // Check that the position is updated correctly
    ASSERT_EQ(particle.getVitesse()[0], 4.7);
    ASSERT_EQ(particle.getVitesse()[1], 5.8);
    ASSERT_EQ(particle.getVitesse()[2], 6.9);
}