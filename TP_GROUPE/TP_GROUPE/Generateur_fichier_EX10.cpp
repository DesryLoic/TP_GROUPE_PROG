#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

int main() {
    // Générateur aléatoire
    mt19937 rng(time(nullptr));

    // Génération aléatoire de la capacité et du nombre d'objets
    uniform_int_distribution<int> distCapacite(30, 50);  // Capacité du véhicule entre 30 et 50
    uniform_int_distribution<int> distNbObjets(5, 15);   // Nombre d'objets entre 5 et 15
    uniform_int_distribution<int> distConso(5, 15);      // Consommation par objet
    uniform_int_distribution<int> distBenef(1, 8);       // Bénéfice par objet

    int capaciteVehicule = distCapacite(rng);
    int nbObjets = distNbObjets(rng);

    // Création (ou écrasement) du fichier
    ofstream fichier("../../../../TP_GROUPE/P1_genere.txt", ios::trunc); // <-- ios::trunc écrase le fichier
    if (!fichier) {
        cerr << "Erreur : impossible de créer le fichier." << endl;
        return 1;
    }

    // Première ligne : capacité et nombre d'objets
    fichier << capaciteVehicule << " " << nbObjets << endl;

    // Génération des objets
    for (int i = 1; i <= nbObjets; ++i) {
        int consommation = distConso(rng);
        int benefice = distBenef(rng);
        fichier << i << " " << consommation << " " << benefice << endl;
    }

    fichier.close();
    cout << "Fichier P1_genere.txt généré avec succès." << endl;
    cout << "Capacité : " << capaciteVehicule << ", Nombre d'objets : " << nbObjets << endl;

    return 0;
}
