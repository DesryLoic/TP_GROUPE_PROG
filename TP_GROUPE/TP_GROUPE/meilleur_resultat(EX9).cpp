#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

int main() {
    //ouvre le fichier resultat.txt et crée le fichier meilleure_P1.txt
    ifstream fichier("../../../../TP_GROUPE/resultat.txt");
    ofstream meilleur("../../../../TP_GROUPE/meilleure_P1.txt");

    if (!fichier) {
        cerr << "Erreur : le fichier resultat.txt n'a pas pu être ouvert." << endl;
        return 1;
    }

    string ligne;
    int bestGraine = -1;
    double bestScore = 0;
    string bloc, meilleurBloc;
    bool inBloc = false;

    //On regarde chaque ligne du fichier resultat.txt jusqu'à trouver === Résumé
    while (getline(fichier, ligne)) {
        if (ligne.find("=== Résumé") == 0) {
            bloc = ligne + "\n";
            inBloc = true;
        }
        //Si on est dans un bloc, alors on cherche le score pondéré
        else if (inBloc) {
            bloc += ligne + "\n";
            if (ligne.find("Score pondere") != string::npos) {
                size_t pos = ligne.find(":");
                if (pos != string::npos) {
                    string scoreStr = ligne.substr(pos + 1);
                    stringstream ss(scoreStr);

                    double score;
                    ss >> score;
                    //Si le score est meilleur que le précédent meilleur score, on le remplace
                    if (score > bestScore) {
                        bestScore = score;
                        meilleurBloc = bloc;

                        // Récupérer la réplication
                        size_t posRep = bloc.find("Réplication : ");
                        if (posRep != string::npos) {
                            sscanf(bloc.c_str() + posRep, "Réplication : %d", &bestGraine);
                        }
                    }
                }

                inBloc = false;
            }

        }
    }
    //On écrit dans meilleure_P1.txt le bloc ayant le meilleur résultat
    if (!meilleurBloc.empty()) {
        meilleur << "=== Meilleure solution pour P1 ===\n";
        meilleur << meilleurBloc;
    }
    else {
        meilleur << "Aucune solution trouvée.\n";
    }

    fichier.close();
    meilleur.close();

    if (bestGraine == -1) {
        cout << "Aucune replication valide trouvee." << endl;
    }
    else {
        cout << "Meilleure replication pour P1 : " << bestGraine << " (Score pondere : " << bestScore << ")" << endl;
    }

    return 0;
}
