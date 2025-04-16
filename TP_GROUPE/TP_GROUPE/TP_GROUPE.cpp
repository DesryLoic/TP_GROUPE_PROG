#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <ctime>
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
    ifstream fichier(nomFichier);//essaye de lire le fichier et affiche un message d'erreur s'il ne peut pas
    if (!fichier) {
        cerr << "Erreur à l'ouverture du fichier " << nomFichier << endl;
        return false;
    }
    //On range dans donnees les informations correspondant à capaciteVehicule et nb_produits
    fichier >> donnees.capaciteVehicule >> donnees.nb_produits;

    //Pour chaque lignes restantes dans le fichier, on prends les informations correspondant à l'id, à consommation et à benefice, que l'on range dans p
    //et qui sera ajouter à la liste des produits de donnees
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
        cerr << "Erreur à l'ouverture du fichier " << nomFichier << endl;
        return false;
    }

    //On prend le nombre de ville présents dans le fichier et on ignore le prochain élément du fichier (ou risque de décallage et donc une ville serait manquante à la liste)
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
//Fonction pour sélectionner les produits à charger dans le véhicule
vector<Produit> selectionnerProduits(DonneesP1& donnees, int& totalBenefice, int& totalConsommation) {
    vector<Produit> selection;

    //Trie les produits en fonction du rapport benefice/consommation (ordre décroissant)
    sort(donnees.produits.begin(), donnees.produits.end(), [](const Produit& a, const Produit& b) {
        return (double)a.benefice / a.consommation > (double)b.benefice / b.consommation;
        });

    int capaciteRestante = donnees.capaciteVehicule; // Capacité disponible du véhicule
    totalBenefice = 0;
    totalConsommation = 0;

    //Ajoute les produits un par un tant que la capacité restante le permet
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
    srand(time(0)); // Initialisation de la graine aléatoire

    int capaciteRestante = donnees.capaciteVehicule; // Capacité disponible du véhicule
    totalBenefice = 0;
    totalConsommation = 0;

    // Continue tant qu'il reste de la capacité et des produits à sélectionner
    while (capaciteRestante > 0 && !donnees.produits.empty())
    {
        // Trier les produits par le rapport bénéfice/consommation (ordre décroissant)
        sort(donnees.produits.begin(), donnees.produits.end(), [](const Produit& a, const Produit& b)
            { return (double)a.benefice / a.consommation > (double)b.benefice / b.consommation; });

        // Vérification du nombre de produits disponibles
        int nbProduits = donnees.produits.size();
        if (nbProduits == 1)
        {
            // Si seulement un produit reste, on le sélectionne directement si la capacité le permet
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
            // Si plusieurs produits restent, on choisit aléatoirement entre les deux premiers produits
            int i = rand() % 2; // Tirage aléatoire pour choisir entre les deux premiers produits

            // Vérification que le produit choisi n'excède pas la capacité restante
            if (donnees.produits[i].consommation <= capaciteRestante)
            {
                selection.push_back(donnees.produits[i]);
                capaciteRestante -= donnees.produits[i].consommation;
                totalBenefice += donnees.produits[i].benefice;
                totalConsommation += donnees.produits[i].consommation;

                // Retirer le produit sélectionné de la liste des produits disponibles
                donnees.produits.erase(donnees.produits.begin() + i);
            }
            else
            {
                // Si le produit ne peut pas être sélectionné, on l'ignore et on passe au suivant
                donnees.produits.erase(donnees.produits.begin() + i);
            }
        }
    }

    return selection;
}


//argc est le nombre d'arguments passé dans le programme, et argv un tableau contenant ces arguments
int main(int argc, char* argv[]) {
    /**** Question 2 ****/
    //vérifie qu'il y a le bon nombre d'argument passé en paramètre (sachant que argv[0] correspond à ./lecture_fichiers qui n'a pas besoin d'être précisé dans les arguments)
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <fichierP1> <fichierP2>" << endl;
        return 1;
    }

    DonneesP1 donneesP1;
    DonneesP2 donneesP2;

    //exécute les 2 fonctions remplissant les structure de données et vérifie si elles ont été exécuté sans problème.
    if (!lireFichierP1(argv[1], donneesP1)) return 1;
    if (!lireFichierP2(argv[2], donneesP2)) return 1;

    //affiche les différents éléments des 2 fichiers qui ont été stockés dans donneesP1 et donneesP2
    cout << "Donnees P1 :\nCapacite vehicule: " << donneesP1.capaciteVehicule << "\nNombre de produits: " << donneesP1.nb_produits << endl;
    for (const auto& p : donneesP1.produits) {
        cout << "Produit " << p.id << " - Consommation: " << p.consommation << ", Benefice: " << p.benefice << endl;
    }

    cout << "\nDonnees P2 :\nNombre de villes: " << donneesP2.nb_villes << endl;
    for (const auto& ville : donneesP2.villes) {
        cout << ville << endl;
    }

    cout << "\nMatrice des distances:" << endl;
    for (const auto& ligne : donneesP2.matriceDistances) {
        for (int val : ligne) {
            cout << val << " ";
        }
        cout << endl;
    }



    int totalBenefice = 0;
    int totalConsommation = 0;
    /**** Question 4 ****/
    //vector<Produit> selection = selectionnerProduits(donneesP1, totalBenefice, totalConsommation);

    /**** Question 5 ****/
    vector<Produit> selection = selectionnerProduitsAleatoires(donneesP1, totalBenefice, totalConsommation);

    cout << "\nProduits selectionnes :" << endl;
    for (const auto& p : selection) {
        cout << "Produit " << p.id << " - Consommation: " << p.consommation << ", Benefice: " << p.benefice << endl;
    }

    cout << "\nBilan de la selection :" << endl;
    cout << "Benefice total : " << totalBenefice << endl;
    cout << "Energie consommee : " << totalConsommation << " / " << donneesP1.capaciteVehicule << endl;



    return 0;
}