/**
 * @file Particle.cxx
 *
 * @brief a class to manipulate particles
 */

#include "../include/Particle.hxx"
#include <fstream>
#include "Particle.hxx"
/**
 * Particle constructor, creates a particle that has a random position(_position) and velocity  (_vitesse)
 * @param dim
 */
Particle::Particle(int dim) : _dim(dim){
    std::random_device rd;
    std::mt19937 mt(rd());
    double vecteur[dim];
    for(int i = 0; i < dim; i++){
        vecteur[i] = dist1(mt) * 100;
    }
    Vecteur pos(dim, vecteur);
    _position = pos;
    for(int i = 0; i < dim; i++){
        vecteur[i] = dist1(mt) * 1000;
    }
    Vecteur vitesse(dim, vecteur);
    _vitesse = vitesse;
    _masse = dist1(mt) * .1;
    for(int i = 0; i < dim; i++){
        vecteur[i] = 0.0;
    }
    Vecteur force(dim, vecteur);
    _force = force;
    _old_force = force;
    _id = count++;
    _categorie = "A";
}

/**
 * Particle constructor, with the important information about the particle (position, velocity, mass ...)
 * @param dim
 * @param position
 * @param vitesse
 * @param masse
 * @param categorie
 */
Particle::Particle(int dim, double position[], double vitesse[], double masse, const std::string &categorie)
        :  _dim(dim), _masse(masse), _categorie(categorie), _position(dim), _vitesse(dim), _force(dim), _old_force(dim), _cumulative_force(dim) {
    for(int i = 0; i < dim; i++){
        _position.setI(i, position[i]);
        _vitesse.setI(i, vitesse[i]);
    }        
    _id = count++;
}



int Particle::getId() const{
    return _id;
}
double Particle::getMasse() const{
    return _masse;
}

Vecteur &Particle::getPosition(){
    return _position;
}
Vecteur &Particle::getForce(){
    return _force;
}
Vecteur &Particle::getOldForce(){
    return _old_force;
}

Vecteur &Particle::getCumulativeForce()
{
    return _cumulative_force;
}

void Particle::setCumulativeForce(const Vecteur &force){
    _cumulative_force = force;
}
Vecteur &Particle::getVitesse()
{
    return _vitesse;
}

void Particle::setVitesse(const Vecteur &vitesse) {
    _vitesse = vitesse;
}
void Particle::setMasse(double masse){
    _masse = masse;
}
std::string &Particle::getCategorie(){
    return _categorie;
}


void Particle::setPosition(const Vecteur &position) {
    _position = position;
}

void Particle::setCategorie(const std::string &categorie) {
    _categorie = categorie;
}

void Particle::setForce(const Vecteur &force) {
    _force = force;
}

void Particle::setOldForce(const Vecteur &force){
    _old_force = force;
}
/**
 * fast power function for integers, faster than the usual pow from <math.h>
 * @param base
 * @param exponent
 * @return the result of the operation base ^ {exponent}
 */
double fast_pow(double base, int exponent){
    double result = 1.0;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return result;
}
/**
 * prints the position of the particle so we can keep track of it
 */
void Particle::printParticle(){
    std::cout << " The position of Particle N° " << _id << " is "<< _position <<  std::endl;
}
int operator==(const Particle& p1, const Particle& p2){
    return p1.getId() == p2.getId();
}
/**
 * computes the distance between two particles
 * @param other
 * @return distance
 */
double Particle::distance(Particle &other) const{
    if(_id == other.getId()){
        return 0.0;
    }
    int dim = _position.getDim();
    double distance;
    for(int i = 0; i < dim; i++){
        distance += fast_pow(_position[i] - other.getPosition()[i], 2);
    }
    return pow(distance, .5);
}

/**
 * Computes the Gravitational force between the particle and the other one
 * @param other
 * @return "Vecteur" of force components
 */
Vecteur Particle::compute_force(const std::shared_ptr<Particle>& other) const{
    int dim = _position.getDim();
    double distance = Particle::distance(*other);
    Vecteur force(dim);
    if(distance == 0){
        return force;
    }
    double total_force = (_masse * other->getMasse()) / pow(distance, 2);
    force =  (1 / distance) * total_force * (other->getPosition() - _position);
    return force;
}

/**
 * computes force between two particles using potential force
 * @param other
 * @param r_cut threshold, we do not compute the force if the distance if greater than r_cut
 * @return Vecteur, containing the components of the force
 */
Vecteur Particle::compute_force_2(const std::shared_ptr<Particle>& other, double r_cut) const{
    int dim = _position.getDim();
    double distance = Particle::distance(*other);
    Vecteur force(dim);
    if(distance == 0 || distance > r_cut){
        return force;
    }
    int k = fast_pow(SIGMA / distance, 6);
    double total_force = 24 * EPSILON / distance * k * (1 - 2 * k);
    force =  (1 / distance) * total_force * (other->getPosition() - _position);
    return force;
}

/**
 * computes all the interaction forces between the particle and a vector of particles, and update the particle
 * @param particles
 */
void Particle::compute_all_forces(std::vector<std::shared_ptr<Particle>> &particles){
    for(auto& p : particles){
        if(_id < p->getId()){
            Vecteur temp = compute_force(p);
            _cumulative_force += temp;
            // to divide the complexity by 2, we can store use the formula : F_ij = - F_ji
            p->getCumulativeForce() -= temp;
        }
    }
    setForce(_cumulative_force);
    reset_cumulative_force();
}

void Particle::update_position(double dt){
    _position = _position + dt * ( _vitesse + .5 * (dt / _masse) * _force) ;
}

void Particle::update_vitesse(double dt){
    _vitesse = _vitesse +  dt * .5 /_masse * (_force + _old_force);
}

void  Particle::update_old_force(){
    for(int i = 0; i < _old_force.getDim(); i++){
        _old_force.setI(i, _force[i]);
    }
}

void Particle::reset_force(){
    for(int i = 0; i < _force.getDim(); i++){
        _force.setI(i, 0.0);
    }
}
void Particle::reset_old_force(){
    for(int i = 0; i < _force.getDim(); i++){
        _old_force.setI(i, 0.0);
    }
}
void Particle::reset_cumulative_force(){
    for(int i = 0; i < _force.getDim(); i++){
        _cumulative_force.setI(i, 0.0);
    }
}

/**
 * StromerVerlet implementation
 * @param particles 
 * @param t_end
 * @param dt
 */
void StormerVerlet(std::vector<std::shared_ptr<Particle>>& particles, double t_end, double dt){
    for(auto& p : particles){
        p->compute_all_forces(particles);
    }
    double t;
    while (t < t_end){
        t += dt;
        for(auto& p : particles){
            p->update_position(dt);
            p->reset_old_force();
            p->update_old_force();
        }
        for(auto& p : particles){
            p->compute_all_forces(particles);
        }
        for(auto& p : particles){
            p->update_vitesse(dt);
        }
    }
}