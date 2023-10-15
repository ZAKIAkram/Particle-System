#include "../include/Univers.hxx"
#include <chrono>
int main(){
    int nb_particles = 1000;
    int dim = 2;
    double vecteur[2] = {250, 40};
    Vecteur Ld(2, vecteur);
    std::vector<std::shared_ptr<Particle>> particles;
    for(int i = 0; i < nb_particles; i++){
        particles.push_back(std::make_shared<Particle>(dim));
    }
    auto start = std::chrono::steady_clock::now();
    Univers univers(dim, nb_particles, particles, Ld, 2.5, 0);
    // Univers univers(dim, nb_particles);
    auto end = std::chrono::steady_clock::now();
    std::cout << "debut simulation" << std::endl;
    for(auto& c : univers.getGrid()){
        std::cout << c << std::endl;
    }
}