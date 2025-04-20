#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>

using namespace std;

int main() {
    //ouvre le fichier resultat.txt et cr�e le fichier meilleure_P1.txt
    ifstream fichier("../../../../TP_GROUPE/resultat.txt");
    ofstream meilleur("../../../../TP_GROUPE/meilleure_P1.txt");

    if (!fichier) {
        cerr << "Erreur : le fichier resultat.txt n'a pas pu �tre ouvert." << endl;
        return 1;
    }

    string ligne;
    int bestGraine = -1;
    double bestScore = 0;
    string bloc, meilleurBloc;
    bool inBloc = false;

    //On regarde chaque ligne du fichier resultat.txt jusqu'� trouver === R�sum�
    while (getline(fichier, ligne)) {
        if (ligne.find("=== R�sum�") == 0) {
            bloc = ligne + "\n";
            inBloc = true;
        }
        //Si on est dans un bloc, alors on cherche le score pond�r�
        else if (inBloc) {
            bloc += ligne + "\n";
            if (ligne.find("Score pondere") != string::npos) {
                size_t pos = ligne.find(":");
                if (pos != string::npos) {
                    string scoreStr = ligne.substr(pos + 1);
                    stringstream ss(scoreStr);

                    double score;
                    ss >> score;
                    //Si le score est meilleur que le pr�c�dent meilleur score, on le remplace
                    if (score > bestScore) {
                        bestScore = score;
                        meilleurBloc = bloc;

                        // R�cup�rer la r�plication
                        size_t posRep = bloc.find("R�plication : ");
                        if (posRep != string::npos) {
                            sscanf(bloc.c_str() + posRep, "R�plication : %d", &bestGraine);
                        }
                    }
                }

                inBloc = false;
            }

        }
    }
    //On �crit dans meilleure_P1.txt le bloc ayant le meilleur r�sultat
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
        cout << "Aucune replication valide trouvee." << endl;
    }
    else {
        cout << "Meilleure replication pour P1 : " << bestGraine << " (Score pondere : " << bestScore << ")" << endl;
    }

    return 0;
}
