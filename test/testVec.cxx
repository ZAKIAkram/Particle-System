#include "../include/Vecteur.hxx"

int main(){
    double vecteur[3] = {1.0, 2.0, 3.0};
    double vecteur1[3] = {4.0, 5.0, 6.0};
    Vecteur vec1(3, vecteur);
    Vecteur vec2(3, vecteur1);
    Vecteur vec3 = vec1 + vec2;
    std::cout << vec3 <<std::endl;
    std::cout << vec3[2] << std::endl;

}