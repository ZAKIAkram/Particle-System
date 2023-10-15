##### usage :
mkdir build
cd build
cmake ..

il y'a 11 test dans le répértoire test, pour tester, il suffit d'ecrire la commande : 

make <nom_du_test>

puis l'éxecuter : 
./test/<nom_du_test>

Parmi les 11 tests, il y'a des : "google_tests", les noms des gtests sont de la forme : <nom_du_test>_test.cxx 
les autres tests sont des tests normaux.
Le test testCollision.cxx dans le répértoire test est le test qui fait la simulationdu lab 4. mais il prend du temps.

Pour générer la documentation doxygen il faut effectuer la command suivante : 

- cd doc
- doxygen doxyfilerc

Une documentation est générée dans le folder docu
