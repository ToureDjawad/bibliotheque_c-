#include <iostream> // Pour les entrées/sorties standard
#include <limits> // Pour numeric_limits (nettoyage du memoire tampon de cin )
#include "fonctions.hpp" // Inclure le fichier d'en-tête pour les structures et fonctions de la bibliothèque

using namespace std;

int main() {
    
    //Création de la variable principale qui contient toute la bibliothèque
    Bibliotheque bibliotheque;

    //hargement de la configuration (app.conf)
    chargeAppConf(bibliotheque);
    //Chargement de la bibliothèque depuis le fichier (s'il existe)
    if (chargerBibliotheque(bibliotheque)) {
    } else {
        initBibliotheque(bibliotheque);
    }

    bool naviguer = true;

    // Boucle principale du menu
    while (naviguer) {
        cleanEcran();
        logo(bibliotheque);
        cout << "Menu principal" << endl;
        cout <<"---------------------------------------------------" << endl;
        cout << "1. Consulter les références" << endl;
        cout << "2. Gérer les références" << endl;
        cout << "3. Chercher une référence" << endl;
        cout << "4. Exporter en HTML" << endl;
        cout << "5. Paramètres" << endl;
        cout << "6. Quitter" << endl;
        cout << endl << "> Votre choix ";

        int choix;
        // si l'utilisateur ne rentre pas un nombre ors des options proposée dans le menu on netoye cin et ignore tout le reste de la ligne jusqu'au saut de ligne
        if (!(cin >> choix)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
            continue;
        }
        // On nettoie les entrer qui traîne
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (choix) {
            case 1:
                printLivre(bibliotheque);
                break;
            case 2: 
            {
                cleanEcran();
                logo(bibliotheque);
                // si la gestion des références retourne false on quitte le menu principal
                if (refLivre(bibliotheque) == false) {
                    naviguer = false; 
                }
                break;
            }
            case 3: 
                cleanEcran();
                logo(bibliotheque);
                searchLivres(bibliotheque);
                break;

            case 4:
                exporterHTML(bibliotheque);
                break;

            case 5:
                cleanEcran();
                logo(bibliotheque);
                modifierParam(bibliotheque);
                break;

            case 6: // Quitter
                cleanEcran();
                logo(bibliotheque);
                cout << "1. Sauvegarder et Quitter" << endl;
                cout << "2. Quitter sans sauvegarder" << endl;               
                cout << "Votre choix > ";

                int choixSortie;
                // Vérification si l'utilisateur tape le bon nombre
                if (cin >> choixSortie) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Nettoyage du reste de la ligne

                    if (choixSortie == 1) {
                        saveBibliotheque(bibliotheque);
                        naviguer = false; // Arrête la boucle while
                    }
                    else if (choixSortie == 2) {
                        naviguer = false; // Arrête la boucle while
                    }
                } 
                else {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Saisie invalide. Retour au menu." << endl;
                    sortie();
                }
                break;

            default:
                // Si l'utilisateur entre un nombre hors des options proposées
                cout << "Choix invalide." << endl;
                sortie();
                break;
        }
    }
    cout << "Au revoir ! " << endl;
    return 0;
}