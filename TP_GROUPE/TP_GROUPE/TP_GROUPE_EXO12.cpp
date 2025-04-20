#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
#include <vector>


using namespace std;
using namespace chrono;

// Génère un fichier de produits (P1)


void genererFichierP1(const string& cheminFichier, int nbProduits, int capaciteMin = 100, int capaciteMax = 200) {
   
    ofstream fichier("../../../../TP_GROUPE/P1_genere.txt", ios::trunc); // <-- ios::trunc écrase le fichier
    if (!fichier) {
        cerr << "Erreur : impossible de créer le fichier." << endl;
        return; 
    }

    // Initialisation des générateurs aléatoires
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distConso(1, 20);
    uniform_int_distribution<int> distBenef(1, 10);
    uniform_int_distribution<int> distCapacite(capaciteMin, capaciteMax);

    // Capacité du véhicule (aléatoire)
    int capacite = distCapacite(gen);
    fichier << capacite << " " << nbProduits << endl;

    // Génération des produits avec consommation et bénéfice aléatoire
    for (int i = 1; i <= nbProduits; ++i) {
        int conso = distConso(gen);
        int benef = distBenef(gen);
        fichier << i << " " << conso << " " << benef << endl;
    }

    fichier.close();
    cout << "Fichier P1EXO12 généré avec " << nbProduits << " produits dans " << cheminFichier << endl;
}

// Génère un fichier de distances entre villes (P2)
void genererFichierP2(const string& cheminFichier, int nbVilles) {
   
    ofstream fichier(cheminFichier, ios::trunc);
    if (!fichier) {
        cerr << "Erreur : impossible de créer le fichier P2." << endl;
        return;
    }

    // Initialisation des générateurs aléatoires
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distDistance(10, 100);

    // Premier élément : nombre de villes
    fichier << nbVilles << endl;

    // Liste des noms de villes
    for (int i = 0; i < nbVilles; ++i) {
        fichier << "Ville_" << i << endl;
    }

    // Matrice carrée des distances entre villes
    for (int i = 0; i < nbVilles; ++i) {
        for (int j = 0; j < nbVilles; ++j) {
            if (i == j) fichier << 0 << " ";
            else fichier << distDistance(gen) << " ";
        }
        fichier << endl;
    }

    fichier.close();
    cout << "Fichier P2EXO12 généré avec " << nbVilles << " villes dans " << cheminFichier << endl;
}



