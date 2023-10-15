/**
 * @file Univers.hxx
 *
 * @brief Universe simulation using stormerVerlet integration
 */
#pragma once

#include <math.h>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include <math.h>
#include "Particle.hxx"
#include "Cell.hxx"
#define VTK 1
#define FPS 30
/**
 * Univers class, contains a vector of particles, and is divided into a grid to lower the computations
 */
class Univers{
public:
//TODO : _grid private 

    Univers(int dim, int nb_particles);
    Univers(int dim, int nb_particles, const std::vector<std::shared_ptr<Particle>> &particles);
    Univers(int dim, int nb_particles,std::vector<std::shared_ptr<Particle>>& particles, Vecteur Ld, double r_cut, int type);
    // void place_particle(const Particle& particle);
    void compute_all_forces();
    void compute_all_forces_2();
    void compute_all_forces_1D();
    void compute_all_forces_2D();
    void compute_all_forces_3D();
    int getCellIndex(Vecteur& position);
    int boundary_hit(const Vecteur& position);
    void handle_reflections(std::shared_ptr<Particle> & p);
    void handle_periodic_mvt(std::shared_ptr<Particle>& p);
    int getNbParticles();
    std::vector<Cell>& getGrid();
    void move_particle(std::shared_ptr<Particle> p, int cell_index_src, int cell_index_dest);
    void StormerVerlet(double t_end, double dt);
    void print_univers_state_in_VTK(std::ofstream& out);
    std::vector<std::shared_ptr<Particle>> &getParticles();
private:
    std::vector<Cell> _grid;
    int _nb_particles;
    int _dim;
    Vecteur _Ld;
    double _r_cut;
    std::vector<std::shared_ptr<Particle>> _particles;
    Vecteur _grid_size;
    int _size;
    int _type; // 0 for absorption, 1 for reflexion and 2 for periodic
};
