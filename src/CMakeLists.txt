# Créer une bibliothèque à partir d'un ensemble de fichier sans main

#add_library(univers Particle.cxx Univers.cxx Cell.cxx Vecteur.cxx)

add_library(univers Univers.cxx)
add_library(particle Particle.cxx)
add_library(cell Cell.cxx)
add_library(vecteur Vecteur.cxx)