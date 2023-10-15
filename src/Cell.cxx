/**
 * @file Cell.cxx
 *
 * @brief a cell class, helps representing a Univers using a grid of cells
 */

#include "../include/Cell.hxx"

Cell::Cell(){}
/**
 * inserts a particle in the cell
 * @param particle
 */
void Cell::insert_particle(std::shared_ptr<Particle> particle) {
        _particles.insert(particle);
        _nb_particles++;
}
/**
 * Removes a particle from the cell
 * @param particle
 */
void Cell::remove_particle(std::shared_ptr<Particle> particle) {
        _particles.erase(particle);
        _nb_particles--;
}

std::set<std::shared_ptr<Particle>> &Cell::getParticles(){
    return _particles;
}

int Cell::getNbParticles(){
    return _nb_particles;
}

std::ostream & operator<<(std::ostream & out, Cell &cell){
    out << cell.getNbParticles();
    return out;
}