#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

int main() {
    ifstream fichier("resultat.txt");
    ofstream meilleur("meilleure_P1.txt");

    if (!fichier) {
        cerr << "Erreur : le fichier resultat.txt n'a pas pu �tre ouvert." << endl;
        return 1;
    }

    string ligne;
    int bestGraine = -1;
    double bestScore = 0;
    string bloc, meilleurBloc;
    bool inBloc = false;

    while (getline(fichier, ligne)) {
        if (ligne.find("=== R�sum�") == 0) {
            bloc = ligne + "\n";
            inBloc = true;
        }
        else if (inBloc) {
            bloc += ligne + "\n";
            if (ligne.find("Score pondere") != string::npos) {
                double score;
                sscanf(ligne.c_str(), "Score pondere : %lf", &score);

                if (score > bestScore) {
                    bestScore = score;
                    meilleurBloc = bloc;

                    // R�cup�rer la r�plication : ligne "R�plication : x"
                    size_t pos = bloc.find("R�plication : ");
                    if (pos != string::npos) {
                        sscanf(bloc.c_str() + pos, "R�plication : %d", &bestGraine);
                    }
                }

                inBloc = false; // fin du bloc
            }
        }
    }

    if (!meilleurBloc.empty()) {
        meilleur << "=== Meilleure solution pour P1 ===\n";
        meilleur << meilleurBloc;
    }
    else {
        meilleur << "Aucune solution trouv�e.\n";
    }

    fichier.close();
    meilleur.close();

    if (bestGraine == -1) {
        cout << "Aucune r�plication valide trouv�e." << endl;
    }
    else {
        cout << "Meilleure r�plication pour P1 : " << bestGraine << " (Score pond�r� : " << bestScore << ")" << endl;
    }

    return 0;
}
