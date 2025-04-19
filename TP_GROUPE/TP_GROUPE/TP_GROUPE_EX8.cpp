#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iomanip>
/************ QUESTION 2 ***********/
using namespace std;
struct Produit
{
    int id;
    int consommation;
    int benefice;
};

struct DonneesP1
{
    int capaciteVehicule;
    int nb_produits;
    vector<Produit> produits; //liste des produits (id/consommation/benefice)
};

struct DonneesP2
{
    int nb_villes;
    vector<string> villes;
    vector<vector<int>> matriceDistances; //matrice d'entier contenant les distances entre chaque villes
};

bool lireFichierP1(const string& nomFichier, DonneesP1& donnees) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        cerr << "[ERREUR] Impossible d�ouvrir le fichier : " << nomFichier << endl;
        exit(1); // ou return DonneesP1(); si tu pr�f�res g�rer plus doucement
    }
    //On range dans donnees les informations correspondant � capaciteVehicule et nb_produits
    fichier >> donnees.capaciteVehicule >> donnees.nb_produits;

    //Pour chaque lignes restantes dans le fichier, on prends les informations correspondant � l'id, � consommation et � benefice, que l'on range dans p
    //et qui sera ajouter � la liste des produits de donnees
    for (int i = 0; i < donnees.nb_produits; ++i) {
        Produit p;
        fichier >> p.id >> p.consommation >> p.benefice;
        donnees.produits.push_back(p);
    }
    //on ferme le fichier
    fichier.close();
    return true;
}

bool lireFichierP2(const string& nomFichier, DonneesP2& donnees) {
    ifstream fichier(nomFichier);//essaye de lire le fichier et affiche un message d'erreur s'il ne peut pas
    if (!fichier) {
        cerr << "Erreur � l'ouverture du fichier " << nomFichier << endl;
        return false;
    }

    //On prend le nombre de ville pr�sents dans le fichier et on ignore le prochain �l�ment du fichier (ou risque de d�callage et donc une ville serait manquante � la liste)
    fichier >> donnees.nb_villes;
    fichier.ignore();

    //rajoute les villes dans la liste villes de donnees
    donnees.villes.resize(donnees.nb_villes);
    for (int i = 0; i < donnees.nb_villes; ++i) {
        getline(fichier, donnees.villes[i]);
    }

    //rajoute les distances entre les villes dans la matrice de donnees
    donnees.matriceDistances.resize(donnees.nb_villes, vector<int>(donnees.nb_villes));
    for (int i = 0; i < donnees.nb_villes; ++i) {
        for (int j = 0; j < donnees.nb_villes; ++j) {
            fichier >> donnees.matriceDistances[i][j];
        }
    }
    //on ferme le fichier
    fichier.close();
    return true;
}


/************ QUESTION 4 ***********/
//Fonction pour s�lectionner les produits � charger dans le v�hicule
vector<Produit> selectionnerProduits(DonneesP1& donnees, int& totalBenefice, int& totalConsommation) {
    vector<Produit> selection;

    //Trie les produits en fonction du rapport benefice/consommation (ordre d�croissant)
    sort(donnees.produits.begin(), donnees.produits.end(), [](const Produit& a, const Produit& b) {
        return (double)a.benefice / a.consommation > (double)b.benefice / b.consommation;
        });

    int capaciteRestante = donnees.capaciteVehicule; // Capacit� disponible du v�hicule
    totalBenefice = 0;
    totalConsommation = 0;

    //Ajoute les produits un par un tant que la capacit� restante le permet
    for (const auto& produit : donnees.produits) {
        if (produit.consommation <= capaciteRestante) {
            selection.push_back(produit);
            capaciteRestante -= produit.consommation;
            totalBenefice += produit.benefice;
            totalConsommation += produit.consommation;
        }
    }

    return selection;
}

/************ QUESTION 5 ***********/

vector<Produit> selectionnerProduitsAleatoires(DonneesP1& donnees, int& totalBenefice, int& totalConsommation)
{
    vector<Produit> selection;

    int capaciteRestante = donnees.capaciteVehicule; // Capacit� disponible du v�hicule
    totalBenefice = 0;
    totalConsommation = 0;

    // Continue tant qu'il reste de la capacit� et des produits � s�lectionner
    while (capaciteRestante > 0 && !donnees.produits.empty())
    {
        // Trier les produits par le rapport b�n�fice/consommation (ordre d�croissant)
        sort(donnees.produits.begin(), donnees.produits.end(), [](const Produit& a, const Produit& b)
            { return (double)a.benefice / a.consommation > (double)b.benefice / b.consommation; });

        // V�rification du nombre de produits disponibles
        int nbProduits = donnees.produits.size();
        if (nbProduits == 1)
        {
            // Si seulement un produit reste, on le s�lectionne directement si la capacit� le permet
            if (donnees.produits[0].consommation <= capaciteRestante)
            {
                selection.push_back(donnees.produits[0]);
                capaciteRestante -= donnees.produits[0].consommation;
                totalBenefice += donnees.produits[0].benefice;
                totalConsommation += donnees.produits[0].consommation;
            }
            break; // On termine ici car il n'y a plus de produits
        }
        else if (nbProduits > 1)
        {
            // Si plusieurs produits restent, on choisit al�atoirement entre les deux premiers produits
            int i = rand() % 2; // Tirage al�atoire pour choisir entre les deux premiers produits

            // V�rification que le produit choisi n'exc�de pas la capacit� restante
            if (donnees.produits[i].consommation <= capaciteRestante)
            {
                selection.push_back(donnees.produits[i]);
                capaciteRestante -= donnees.produits[i].consommation;
                totalBenefice += donnees.produits[i].benefice;
                totalConsommation += donnees.produits[i].consommation;

                // Retirer le produit s�lectionn� de la liste des produits disponibles
                donnees.produits.erase(donnees.produits.begin() + i);
            }
            else
            {
                // Si le produit ne peut pas �tre s�lectionn�, on l'ignore et on passe au suivant
                donnees.produits.erase(donnees.produits.begin() + i);
            }
        }
    }

    return selection;
}


//argc est le nombre d'arguments pass� dans le programme, et argv un tableau contenant ces arguments
int main(int argc, char* argv[]) {
    /**** Question 2 ****/
    //v�rifie qu'il y a le bon nombre d'argument pass� en param�tre (sachant que argv[0] correspond � ./lecture_fichiers qui n'a pas besoin d'�tre pr�cis� dans les arguments)
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " <fichierP1> <fichierP2> <graine>" << endl;
        return 1;
    }

    int graine = atoi(argv[3]);
    srand(graine);  // Initialisation du g�n�rateur al�atoire avec la graine


    DonneesP1 donneesP1;
    DonneesP2 donneesP2;

    //ex�cute les 2 fonctions remplissant les structure de donn�es et v�rifie si elles ont �t� ex�cut� sans probl�me.
    if (!lireFichierP1(argv[1], donneesP1)) return 1;
    if (!lireFichierP2(argv[2], donneesP2)) return 1;


    int totalBenefice = 0;
    int totalConsommation = 0;

    vector<Produit> selection = selectionnerProduitsAleatoires(donneesP1, totalBenefice, totalConsommation);
    // Calcul pond�r�
    double scorePondere = (totalConsommation > 0) ? static_cast<double>(totalBenefice) / totalConsommation : 0.0;

    std::cout << "\n=== R�sum� (r�plication " << graine << ") ===" << std::endl;
    std::cout << "R�plication : " << graine << std::endl;
    std::cout << "B�n�fice total : " << totalBenefice << std::endl;
    std::cout << "Consommation totale : " << totalConsommation << std::endl;
    std::cout << "Score pondere : " << std::fixed << std::setprecision(2) << scorePondere << endl;




    return 0;
}