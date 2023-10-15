/**
 * @file Univers.cxx
 *
 * @brief Universe simulation using stormerVerlet integration
 */
#include "../include/Univers.hxx"

/**
 * constructor of Universe, creates a random Univers
 * @param dim number of dimensions : 1D, 2D or 3D
 * @param nb_particles number of particles in the univers
 */
Univers::Univers(int dim, int nb_particles) : _dim(dim), _nb_particles(nb_particles){
    std::vector<std::shared_ptr<Particle>> particles;
    particles.reserve(nb_particles); //to avoid copying every element when pushing back a new one
    for(int i = 0; i < nb_particles; i++){
        std::shared_ptr<Particle> particle = std::make_shared<Particle>(dim);
        particles.push_back(particle);
    }
    _particles = particles;
}

Univers::Univers(int dim, int nb_particles, const std::vector<std::shared_ptr<Particle>> &particles) : _nb_particles(nb_particles), _dim(dim),
                                                                                          _particles(particles){}

/**
 * creates a Univers from the given particles vector, and place them in the grid
 * @param dim
 * @param nb_particles
 * @param particles
 * @param Ld
 * @param r_cut
 * @param type
 */
Univers::Univers(int dim, int nb_particles, std::vector<std::shared_ptr<Particle>>& particles, Vecteur Ld, double r_cut, int type) : _nb_particles(nb_particles) , _dim(dim), _Ld(Ld), _r_cut(r_cut),
                                                                                                                           _particles(particles), _grid_size(dim), _type(type) {
    int size = 1;
    for (int i = 0; i < dim; i++) {
        int nc_d = static_cast<int>(_Ld[i] / (double) _r_cut);
        _grid_size.setI(i, nc_d);
        size *= nc_d;
    }
    _size = size;
    _grid.reserve(size);
    for (int i = 0; i < size; i++) {
        _grid.push_back(Cell());
    }
    for (auto &p: particles) {
        int x = p->getPosition()[0] / _r_cut, y = 0, z = 0;
        int sizeX = _grid_size[0], sizeY = 0;
        if (x >= sizeX) {
            continue;
        }
        if (dim >= 2) {
            y = p->getPosition()[1] / _r_cut;
            sizeY = _grid_size[1];
            if (y >= sizeY) {
                continue;
            }
        }
        if (dim >= 3) {
            z = p->getPosition()[2] / _r_cut;
            int sizeZ = _grid_size[2];
            if (z >= sizeZ) {
                continue;
            }
        }
        _grid[x + sizeX * (y + sizeY * z)].insert_particle(p);
    }
}

/**
 * returns the index of the cell of the particle
 * @param position
 * @return cell index
 */
int Univers::getCellIndex(Vecteur& position){
    //the cell index has the form : x + size_X * y + size_X * size_Y * z
    int x = (int)(position[0] / _r_cut), y = 0, z = 0;
        int sizeX = _grid_size[0], sizeY = 0;
        if(_dim >= 2){
            y = (int)(position[0] / _r_cut);
            sizeY = _grid_size[1];
        }
        if(_dim >= 3){
            z = (int)(position[2] / _r_cut);
        }
        int cell_index = x + sizeX  * (y + sizeY * z); 
    return cell_index;
}
std::vector<std::shared_ptr<Particle>> &Univers::getParticles(){
    return _particles;
}      
/**
 * computes all forces between particles in the universe, (without using the grid)
 */
void Univers::compute_all_forces(){
    for(auto& p : _particles){
        p->compute_all_forces(_particles);
    }
}

int Univers::getNbParticles(){
    return _nb_particles;
}
std::vector<Cell>& Univers::getGrid(){
    return _grid;
}

/**
 * computes the forces if the dimension of the Universe is 1, we compute the interactions only between neighbor cells
 */
void Univers::compute_all_forces_1D(){
    // here we could loop through cells using a for each, but we want to know the neighbors since we did not store them, so we can loop
    // through indices
    for(int x = 0; x < _grid_size[0]; x++){
        for(auto&p : _grid[x].getParticles()){
            p->reset_force();
            //neighbors loop
            for(int x_offset = -1; x_offset <= 1; x_offset++){
                int neighbor_x = x + x_offset;
                if(neighbor_x < 0 || neighbor_x >= _grid_size[0]){
                    continue;
                }
                for(auto& p2 : _grid[neighbor_x].getParticles()){
                    Vecteur force = p->compute_force_2(p2, _r_cut);
                    p->setForce(p->getForce() + force);
                }
            }           
        }
    }
}

/**
 * computes the forces of interactions if the dimension of the universe is 2
 */
void Univers::compute_all_forces_2D(){
    for(int x = 0; x < _grid_size[0]; x++){
        for(int y = 0; y < _grid_size[1]; y++){
            for(auto& p : _grid[x + _grid_size[0] * y].getParticles()){
                p->reset_force();
                //Neighbors loop
                for(int x_offset = -1; x_offset <= 1; x_offset++){
                    for(int y_offset = -1; y_offset <= 1; y_offset++){
                        int neighbor_x = x + x_offset;
                        int neighbor_y = y + y_offset;
                        if(neighbor_x < 0 || neighbor_x >= _grid_size[0] || neighbor_y < 0 || neighbor_y >= _grid_size[1]){
                            continue;
                        }
                        int neighbor_index = neighbor_x + neighbor_y * _grid_size[0];
                        if(neighbor_index >= _grid_size[0] * _grid_size[1]){
                            continue;
                        }
                        for(auto& p2 : _grid[neighbor_index].getParticles()){
                            Vecteur force = p->compute_force_2(p2, _r_cut);
                            p->setForce(p->getForce() + force);
                        }
                    }
                }
            }
        }
    }
}
/**
 * computes the forces applied to the particles in a 3D Universe
 */
void Univers::compute_all_forces_3D(){
    for(int x = 0; x < _grid_size[0]; x++){
        for(int y = 0; y < _grid_size[1]; y++){
            for(int z = 0; z < _grid_size[2]; z++){
                for(auto& p : _grid[x + _grid_size[0] * (y + _grid_size[1] * z)].getParticles()){
                    p->reset_force();
                    //neighbors loop
                    for(int x_offset = -1; x_offset <= 1; x_offset++){
                        for(int y_offset = -1; y_offset <= 1; y_offset++){
                            for(int z_offset = -1; z_offset <= 1; z_offset++){
                                int neighbor_x = x + x_offset;
                                int neighbor_y = y + y_offset;
                                int neighbor_z = z + z_offset;
                                if(neighbor_x < 0 || neighbor_x >= _grid_size[0] || neighbor_y < 0 || neighbor_y >= _grid_size[1] ||
                                    neighbor_z < 0 || neighbor_z >= _grid_size[2]){
                                    continue;
                                }
                                int neighbor_index = neighbor_x + _grid_size[0] * (neighbor_y + _grid_size[1] * z);
                                for(auto& p2 : _grid[neighbor_index].getParticles()){
                                    Vecteur force = p->compute_force_2(p2, _r_cut);
                                    p->setForce(p->getForce() + force);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

/**
 * Computes the forces for every dimension
 */
void Univers::compute_all_forces_2(){
    switch(_dim){
        case 1 :
            compute_all_forces_1D();
        case 2 : 
            compute_all_forces_2D();
        case 3 :
            compute_all_forces_3D();
    }
}
/**
 * moves a particle from one cell to another
 * @param p particle to move
 * @param cell_index_src the index of the source cell
 * @param cell_index_dest the index of the destination cell
 */
void Univers::move_particle(std::shared_ptr<Particle> p, int cell_index_src, int cell_index_dest){
    _grid[cell_index_src].remove_particle(p);
    _grid[cell_index_dest].insert_particle(p);
}

/**
 * returns 1 if the particle hits a boundary, 0 if not
 * @param position position of the particle
 * @return integer
 */
int Univers::boundary_hit(const Vecteur& position){
    for (int i = 0; i < position.getDim(); ++i) {
        if ((int)(position[i] / _r_cut) < 0) {
            return 1;
        }
        else if ((int)(position[i] / _r_cut)  >= _grid_size[i]) {
           return 1;
        }
    }
    return 0;
}

/**
 * handler of periodic movement of particles
 * @param p particle
 */
void Univers::handle_periodic_mvt(std::shared_ptr<Particle>& p){
    Vecteur position = p->getPosition();
    for (int i = 0; i < position.getDim(); ++i) {
        if ((int)(position[i] / _r_cut) < 0) {
            p->getPosition()[i] += _grid_size[i];
        }
        else if ((int)(position[i] / _r_cut) >= _grid_size[i]) {
            p->getPosition()[i] -= _grid_size[i]; // Transport to the opposite boundary
        }
    }
}
/**
 * handler of the reflections, it changes the direction of the movement if the particle hits a boundary
 * @param p
 */
void Univers::handle_reflections(std::shared_ptr<Particle>&p){
    Vecteur position = p->getPosition();
    double new_vitesse[position.getDim()];
    for (int i = 0; i < position.getDim(); ++i) {
        if ((int)(position[i] / _r_cut) < 0 || (int)(position[i] / _r_cut) >= _grid_size[i]) {
            new_vitesse[i] = -p->getVitesse()[i];
        }
    }
    Vecteur vitesse(position.getDim(), new_vitesse);
    p->setVitesse(vitesse);
}
/**
 * StormerVerlet algorithm that simulates the movements of the particles in a univers
 * @param t_end end date of the simulation in secondes
 * @param dt the step
 */
void Univers::StormerVerlet(double t_end, double dt){
    compute_all_forces_2();
    double t = 0.0;
    int frame = 0;
    int counter;
    while (t < t_end){
        t += dt;
        if(VTK){
            if(frame % 100 == 0){
                std::ofstream output_file;
                output_file.open("../Demo/VTU_real_simu/frame_" + std::to_string(counter) + ".vtu");
                print_univers_state_in_VTK(output_file);
                output_file.close();
                counter++;
            }
        }
        frame++;
        for(auto& p : _particles){
            Vecteur pos_before = p->getPosition();
            p->update_position(dt);
            Vecteur pos_after_update = p->getPosition();
            if(_type){
                int boundary = boundary_hit(pos_after_update);
                if(boundary){
                    if(_type == 1){
                        handle_reflections(p);
                    }
                    if(_type == 2){
                        handle_periodic_mvt(p);
                    }
                }
            }
            int cell_src = getCellIndex(pos_before), cell_dest = getCellIndex(pos_after_update);
            //updating the cells
            if(cell_src != cell_dest){
                if(!(cell_dest >= _size || cell_dest < 0 || cell_src >= _size || cell_src < 0)){
                    move_particle(p, cell_src, cell_dest);
                }
            }
            p->reset_old_force();
            p->update_old_force();
        }
        compute_all_forces_2();

        for(auto& p : _particles){
            p->update_vitesse(dt);
        }
    }
}

/**
 * prints the state of the universe (the position of the particles and their velocities) ina VTK file so we can visualize
 * the universe in PARAVIEW
 * @param out the file where we want to write Univers state
 */
void Univers::print_univers_state_in_VTK(std::ofstream& out){
    out << "<VTKFile type=\"UnstructuredGrid\" version=\"0.1\" byte_order=\"LittleEndian\">\n";
    out << "  <UnstructuredGrid>\n";
    out << "    <Piece NumberOfPoints=\"" << std::to_string(_nb_particles) << "\" NumberOfCells=\"0\">\n";
    out << "      <Points>\n";
    out << "        <DataArray name=\"Position\" type=\"Float32\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    for (auto& particle : _particles) {
        out << particle->getPosition();
        if(_dim == 2){
            out << std::to_string(0.0) << " ";
        }
        else if(_dim == 1){
            out << std::to_string(0.0) << " " << std::to_string(0.0) << " ";
        }
    }
    
    out << std::endl;
    out << "        </DataArray>\n";
    out << "      </Points>\n";
    out << "      <PointData Vectors=\"vector\">\n";
    out << "        <DataArray type=\"Float32\" Name=\"Velocity\" NumberOfComponents=\"3\" format=\"ascii\">\n";
    for (auto& particle : _particles) {
        out << particle->getVitesse();
        if(_dim == 2){
            out << std::to_string(0.0) << " ";
        }
        else if(_dim == 1){
            out << std::to_string(0.0) << " " << std::to_string(0.0) << " ";
        }
    }
    
    out << std::endl ;
    out << "        </DataArray>\n";
    out << "        <DataArray type=\"Float32\" Name=\"Masse\" format=\"ascii\">\n";
    for (auto& particle : _particles) {
        out << std::to_string(particle->getMasse()) << " ";
    }
    out << std::endl;
    out << "        </DataArray>\n";
    out << "      </PointData>\n";
    out << "      <Cells>\n";
    out << "        <DataArray type=\"Int32\" Name=\"connectivity\" format=\"ascii\">\n";
    out << "        </DataArray>\n";
    out << "        <DataArray type=\"Int32\" Name=\"offsets\" format=\"ascii\">\n";
    out << "        </DataArray>\n";
    out << "        <DataArray type=\"UInt8\" Name=\"types\" format=\"ascii\">\n";
    out << "        </DataArray>\n";
    out << "      </Cells>\n";
    out << "    </Piece>\n";
    out << "  </UnstructuredGrid>\n";
    out << "</VTKFile>";

}