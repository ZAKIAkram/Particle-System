#include "../include/Univers.hxx"

int main(){
    
    std::vector<std::shared_ptr<Particle>> particles;
    particles.reserve(8000);
    double distance = pow(2, 1 / 6);
    for(int i = 0; i < 160; i++){ //160
        for(int j = 0; j < 40; j++){ // 20
            double x = i * distance, y = j * distance;
            double pos[2] = {x, y};
            double vitesse[2] = {0, 0};
            std::shared_ptr<Particle> particle = std::make_shared<Particle>(2, pos, vitesse, 1.0, "rect");
            particles.push_back(particle);
        }
    }
    //the red square : 
    for(int i = 60; i < 100; i++){
        for(int j = 40; j < 80; j++){
            double x = i * distance, y = j * distance;
            double pos[2] = {x, y};
            double vitesse[2] = {0, -10};
            std::shared_ptr<Particle> particle = std::make_shared<Particle>(2, pos, vitesse, 1.0, "square");
            particles.push_back(particle);
        }
    }
    std::cout << particles.size() << std::endl;
    double vecteur[2] = {250, 40};
    Vecteur Ld(2, vecteur);
    Univers univers(2, 8000, particles, Ld, 2.5, 0);
    std::ofstream file;
    univers.StormerVerlet(19.5, .00005);

}
