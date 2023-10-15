#include "../include/Particle.hxx"
#include <vector>
int main(){
    std::vector<std::shared_ptr<Particle>> particles;
    int number_particles = 1000;
    particles.reserve(number_particles);
    for(int i = 0; i < 100; i++){
        particles.push_back(std::make_shared<Particle>(3));
    }
    for(auto& p : particles){
        p->printParticle();
    }
}