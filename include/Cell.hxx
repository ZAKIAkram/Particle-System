/**
 * @file Cell.hxx
 *
 * @brief a cell class, helps representing a Univers using a grid of cells
 */

#include <set>
#include <algorithm>
#include <memory>
#include "Particle.hxx"

/**
 * Cell class, contains a set of particles
 */
class Cell{
public:
    Cell();
    void insert_particle(std::shared_ptr<Particle> particle);
    void remove_particle(std::shared_ptr<Particle> particle);
    std::set<std::shared_ptr<Particle>> &getParticles();
    int getNbParticles();
private:
    int _nb_particles = 0;
    std::set<std::shared_ptr<Particle>> _particles;
};

std::ostream & operator<<(std::ostream& , Cell &);