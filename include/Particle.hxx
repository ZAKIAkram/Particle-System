/**
 * @file Particle.hxx
 *
 * @brief a class to manipulate particles
 */

#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <math.h>
#include <string>
#include <vector>
#include <random>

#include "Vecteur.hxx"

const double  EPSILON = 5.0;
const double SIGMA = 1.0 ;

inline std::uniform_real_distribution<double> dist1(0.0, 1.0);

/**
 * Particle class, we can identify a particle by its _id member, it is unique for every particle
 */
class Particle{
public:
    static int count;
    Particle(int dim);
    Particle(int dim, double position[], double vitesse[], double masse, const std::string &categorie);
    Particle(int dim, const Vecteur &position, const Vecteur &vitesse, double masse,
                       const std::string &categorie, const Vecteur &force);
    void printParticle();
    double distance(Particle& other) const;
    Vecteur compute_force(const std::shared_ptr<Particle>& other) const;
    Vecteur compute_force_2(const std::shared_ptr<Particle>& other, double r_cut) const;
    void compute_all_forces(std::vector<std::shared_ptr<Particle>>& particles);
    void update_position(double dt);
    void update_vitesse(double dt);
    void update_old_force();
    void reset_force();
    void reset_old_force();
    void reset_cumulative_force();
    // Vecteur compute_force2(const Particle& other) const;
    Vecteur& getPosition();
    Vecteur& getVitesse();
    double getMasse() const;
    void setPosition(const Vecteur& position);
    void setVitesse(const Vecteur &vitesse);
    void setMasse(double masse);
    void setCategorie(const std::string &categorie);
    void setForce(const Vecteur &force);
    void setOldForce(const Vecteur &force);
    int getId() const;
    std::string &getCategorie();
    Vecteur &getForce();
    Vecteur &getOldForce();
    Vecteur &getCumulativeForce();
    void setCumulativeForce(const Vecteur&);
private:
    int _dim;
    Vecteur _position;
    Vecteur _vitesse;
    double _masse;
    int _id;
    std::string _categorie;
    Vecteur _force;
    Vecteur _old_force;
    Vecteur _cumulative_force; //algorithmic purpose

};

inline int Particle::count = 0;
int operator==(const Particle& p1, const Particle& p2);
void StormerVerlet(std::vector<std::shared_ptr<Particle>> & particles, double t_end, double dt);

double fast_pow(double base, int exponent);