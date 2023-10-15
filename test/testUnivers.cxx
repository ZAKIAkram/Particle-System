#include "../include/Univers.hxx"
#include <chrono>
int main(){
    int nb_particles = pow(pow(2, 3), 3);
    int dim = 3;

    Univers univers(dim, nb_particles);

    std::cout << "debut simulation" << std::endl;
    auto start = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    univers.compute_all_forces();
    std::cout << "fin simulation" << std::endl;
    
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}