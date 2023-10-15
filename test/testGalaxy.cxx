
#include <iostream>
#include <vector>
#include "../include/Particle.hxx"

int main(){
    std::vector<std::shared_ptr<Particle>> particles;
    particles.reserve(4);
    double pos_soleil[2] = { 0.0, 0.0};
    double pos_terre[2] = { 0.0, 1.0};
    double vitesse_terre[2] = { -1.0, 0.0};
    double pos_jupiter[2] = { 0.0, 5.36};
    double vitesse_jupiter[2] = { -0.425, 0.0};
    double pos_haley[2] = { 34.75, 0.0};
    double vitesse_haley[2] = { 0.0, 0.0296};
    particles.push_back(std::make_shared<Particle>(2, pos_soleil, pos_soleil, 1, "SOleil"));
    particles.push_back(std::make_shared<Particle>(2, pos_terre, vitesse_terre, 3.0e-6, "Terre"));
    particles.push_back(std::make_shared<Particle>(2, pos_jupiter, vitesse_jupiter, 9.55e-4, "Jupiter"));
    particles.push_back(std::make_shared<Particle>(2, pos_haley, vitesse_haley, 1e-14, "Haley"));
    for(auto&p : particles){
        p->printParticle();
    }
    StormerVerlet(particles, 468.5, .015);
    for(auto&p : particles){
        p->printParticle();
    }
}