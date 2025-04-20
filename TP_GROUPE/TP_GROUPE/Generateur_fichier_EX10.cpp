#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

using namespace std;

int main() {
    // G�n�rateur al�atoire
    mt19937 rng(time(nullptr));

    // G�n�ration al�atoire de la capacit� et du nombre d'objets
    uniform_int_distribution<int> distCapacite(30, 50);  // Capacit� du v�hicule entre 30 et 50
    uniform_int_distribution<int> distNbObjets(5, 15);   // Nombre d'objets entre 5 et 15
    uniform_int_distribution<int> distConso(5, 15);      // Consommation par objet
    uniform_int_distribution<int> distBenef(1, 8);       // B�n�fice par objet

    int capaciteVehicule = distCapacite(rng);
    int nbObjets = distNbObjets(rng);

    // Cr�ation (ou �crasement) du fichier
    ofstream fichier("../../../../TP_GROUPE/P1_genere.txt", ios::trunc); // <-- ios::trunc �crase le fichier
    if (!fichier) {
        cerr << "Erreur : impossible de cr�er le fichier." << endl;
        return 1;
    }

    // Premi�re ligne : capacit� et nombre d'objets
    fichier << capaciteVehicule << " " << nbObjets << endl;

    // G�n�ration des objets
    for (int i = 1; i <= nbObjets; ++i) {
        int consommation = distConso(rng);
        int benefice = distBenef(rng);
        fichier << i << " " << consommation << " " << benefice << endl;
    }

    fichier.close();
    cout << "Fichier P1_genere.txt g�n�r� avec succ�s." << endl;
    cout << "Capacit� : " << capaciteVehicule << ", Nombre d'objets : " << nbObjets << endl;

    return 0;
}
