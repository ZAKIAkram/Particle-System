#include "../include/Univers.hxx"

int main(){
    
    std::vector<std::shared_ptr<Particle>> particles;
    particles.reserve(2);
    double position1[2] = {40.0, 10.0};
    double vitesse1[2] = {5.0, 0.0};
    double vitesse2[2] = {-5.0, 0.0};
    double position2[2] = {60.0, 10.0};
    double Ld[2] = {100, 100};
    std::shared_ptr<Particle> particle1 = std::make_shared<Particle>(2, position1, vitesse1, 1, "1");
    std::shared_ptr<Particle> particle2 = std::make_shared<Particle>(2, position2, vitesse2, 1, "2");
    particles.push_back(particle1);
    particles.push_back(particle2);
    Vecteur L_d(2, Ld);
    Univers univers(2, 2,particles, L_d, 10.0, 0);
    univers.StormerVerlet(20, .00005);

}
