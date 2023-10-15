/**
 * @file Vecteur.cxx
 *
 * @brief Vecteur class
 */

#include "../include/Vecteur.hxx"


Vecteur::Vecteur() : _dim(0){}
/**
 * Constructs a Vecteur, that has dim dimensions, and fills it with zeros
 * @param dim
 */
Vecteur::Vecteur(int dim) : _dim(dim){
    //reserve to avoid making copies
    _vecteur.reserve(dim);
    for(int i = 0; i < dim; i++){
        _vecteur.push_back(0.0);
    }
}

Vecteur::Vecteur(int dim, double vecteur[]) : _dim(dim){
    _vecteur.reserve(dim);
    for(int i = 0; i < dim; i++){
        _vecteur.push_back(vecteur[i]);
    }
}

std::vector<double> Vecteur::getValues() const{
    return _vecteur;
}
void Vecteur::setI(int i, double coord){
    _vecteur[i] = coord;
}

int Vecteur::getDim() const{
    return _dim;
}

Vecteur & Vecteur::operator+=(const Vecteur &other){
    for(auto i = 0 ; i < _dim; i++) {
        _vecteur[i] += other[i];
    }
    return *this;
}

Vecteur & Vecteur::operator-=(const Vecteur &other){
    for(auto i = 0 ; i < _dim; i++) {
        _vecteur[i] -= other[i];
    }
    return *this;
}

Vecteur Vecteur::operator*(double k){
    double vecteur[_dim];
    for(int i = 0; i < _dim; i++){
        vecteur[i] = k * _vecteur[i];
    }
  return Vecteur(_dim, vecteur);
}

Vecteur & Vecteur::operator*=(double k){
  for(auto i =0 ; i < _dim; i++) {
    _vecteur[k] *= k;
  }
  return *this;
}


double &Vecteur::operator[](int i){
    return _vecteur[i];
}

double Vecteur::operator[](int i) const{
    return _vecteur[i];
}

std::ostream & operator<<(std::ostream & out, const Vecteur &vec){
    for(auto& v : vec.getValues()){
        out << std::to_string(v) << " ";
    }
    return out;
}

Vecteur operator*(double k, const Vecteur &vec){
    int dim = vec.getDim();
    double vecteur[dim];
    for(int i = 0; i < dim; i++){
        vecteur[i] = k * vec[i];
    }
    return Vecteur(dim, vecteur);
}

Vecteur operator+(const Vecteur &vec1, const Vecteur &vec2){
    int dim = vec1.getDim();
    double vecteur[dim];
    for(int i = 0; i < dim; i++){
        vecteur[i] = vec1[i] + vec2[i];
    }
    return Vecteur(dim, vecteur);
}

Vecteur operator-(const Vecteur &vec1, const Vecteur &vec2){
    int dim = vec1.getDim();
    double vecteur[dim];
    for(int i = 0; i < dim; i++){
        vecteur[i] = vec1[i] - vec2[i];
    }
    return Vecteur(dim, vecteur);
}

