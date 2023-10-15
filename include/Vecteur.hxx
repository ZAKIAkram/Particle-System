/**
 * @file Vecteur.hxx
 *
 * @brief Vecteur class
 */

#pragma once
#include <iostream>
#include <vector>

/**
 * Vecteur class, is representes a 1D, 2D or 3D vector
 */
class Vecteur{
public:
    Vecteur();
    Vecteur(int dim);
    Vecteur(int dim, double vecteur[]);
    std::vector<double> getValues() const;
    void setI(int , double );
    int getDim() const;
    Vecteur &operator+=(const Vecteur& );
    Vecteur &operator-=(const Vecteur& );
    Vecteur operator*(double);
    Vecteur &operator*=(double);
    // Vecteur & operator=(const Vecteur &);
    double &operator[](int);
    double operator[](int) const;
private:
    int _dim;
    std::vector<double> _vecteur;
};

std::ostream & operator<<(std::ostream& , const Vecteur &);

Vecteur operator*(double, const Vecteur &);
Vecteur operator+(const Vecteur &, const Vecteur &);
Vecteur operator-(const Vecteur &, const Vecteur &);