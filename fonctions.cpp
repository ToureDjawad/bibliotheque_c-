#include <iostream> // pour les entrées/sorties standard
#include <limits> // pour gérer les entrées invalides
#include <sstream> // pour transformer des chaînes en flux
#include <fstream>  // Pour ouvrir les portes vers les fichiers (Lire/Ecrire)
#include <algorithm> // Pour min() et max()
#include <cctype>    // Pour convertir en minuscules et minuscules
#include <vector> // Pour utiliser les vecteurs pour stocker les livres et autres listes
#include "fonctions.hpp" // Inclure le fichier d'en-tête pour les structures et fonctions de la bibliothèque
using namespace std;

// Fonction pour effacer l'écran grace à une commande système adaptée au système d'exploitation
void cleanEcran() {
    // Détection du système d'exploitation
    #ifdef _WIN32
        system("cls");  // Pour Windows
    #else
        system("clear"); // Pour Linux (Kali) et Mac
    #endif
}

// fonction pause qui demande à l'utilisateur d'appuyer sur Entrée pour continuer
void sortie() {
    cout << "\nAppuyez sur Entrée pour continuer...";
    cin.ignore(); // Ignore le caractère de nouvelle ligne restant dans le flux d'entrée
}


// fonction pour vérifier la validité d'une date
bool dateValide(int j, int m, int a) {
    if (a < 0 || m < 1 || m > 12 || j < 1) return false;
    int joursDansMois[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    
    // Année bissextile
    if ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0)) {
        joursDansMois[2] = 29;
    }
    return j <= joursDansMois[m];
}
// fonction pour gérer les références des livres
bool refLivre(Bibliotheque& bibliotheque) {
    
    bool resterDansCeMenu = true;
    // Boucle principale du menu de gestion des références des livres
    while (resterDansCeMenu) {
        cleanEcran();
        logo(bibliotheque);
        cout << "Livres" << endl;
        cout << "--------------------------" << endl;
        cout << "1. Ajouter une référence" << endl;
        cout << "2. Importer des références (csv)" << endl;
        cout << "3. Supprimer toutes les références" << endl;
        cout << "4. Retour à l'accueil" << endl;
        cout << "5. Quitter l'application" << endl;
        cout << "\n> Votre choix  ";
        
        int choix;
        // si la saisie est invalide, on recommence la boucle 
        if (!(cin >> choix)) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        if (choix == 1) {
            addLivre(bibliotheque);
        } 
        else if (choix == 2) {
            importLiveCsv(bibliotheque);
        } 
        else if (choix == 3) {
            cleanEcran();
            logo(bibliotheque);
            cout << "> Voulez-vous vraiment supprimer toutes les références ? OUI pour confirmer ou entrer pour annuler : ";
            string confirmation;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(getline(cin, confirmation) && confirmation == "OUI"){
                deletAllRefLivre(bibliotheque);
                cout << "Toutes les références ont été supprimées." << endl;
                sortie();
            } else {
                cout << "Suppression annulée." << endl;
                sortie();
            }
            
        } 
        else if (choix == 4) {
            resterDansCeMenu = false; 
        }
        else if (choix == 5) {
            
            saveBibliotheque(bibliotheque);
            return false; 
        }
    }
    return true; 
}
// fonction pour charger la configuration depuis app.conf
void chargeAppConf(Bibliotheque& bibliotheque) {
    std::ifstream fichier("app.conf"); 

    // Si le fichier n'existe pas, on met une valeur par défaut  0 et on quitte
    if (!fichier.is_open()) {
        bibliotheque.nbrLivreParPage = 0; 
        return;
    }

    // si on lis le nombre de livres par page, on le stocke si non on met 0 par défaut
    if (fichier >> bibliotheque.nbrLivreParPage) {
        fichier.ignore(); // Ignorer le reste de la ligne
    } else {
        bibliotheque.nbrLivreParPage = 0; 
    }

    // Chargement du logo ASCII
    bibliotheque.logo.clear(); // On vide le logo actuel
    std::string ligne;
    // Lecture ligne par ligne jusqu'à la fin du fichier
    while (std::getline(fichier, ligne)) {
        bibliotheque.logo.push_back(ligne);
    }
    fichier.close();// Fermeture du fichier app.conf
}
// Fonction pour afficher le logo de la bibliothèque
void logo(const Bibliotheque& bibliotheque) {
    // Si le logo est vide, afficher un logo par défaut
    if (bibliotheque.logo.empty()) {
        cout << R"(
                .--.                   .---.
            .---|__|           .-.     |~~~|
            .--|===|--|_          |_|     |~~~|--.
            |  |===|  |'\     .---!~|  .--|   |--|
            |%%|   |  |.'\    |===| |--|%%|   |  |
            |%%|   |  |\.'\   |   | |__|  |   |  |
            |  |   |  | \  \  |===| |==|  |   |  |
            |  |   |__|  \.'\ |   |_|__|  |~~~|__|
            |  |===|--|   \.'\|===|~|--|%%|~~~|--|
            ^--^---'--^    `-'`---^-^--^--^---'--'
            )" << endl;
    } else {
        // si non afficher le logo stocké dans la bibliothèque
        for (const string& ligne : bibliotheque.logo) {
            cout << ligne << endl;
        }
    }
    cout << endl;
}

// fonction pour initialiser la bibliothèque si elle n'existe pas
void initBibliotheque(Bibliotheque& bibliotheque) {
    cout << "> Titre de la bibliothèque : ";
    getline(cin, bibliotheque.titre);

    cout << "> Description (ligne vide pour finir) : ";
    getline(cin, bibliotheque.descriptionBiblio);
    sortie();
}

// fonction pour ajouter un livre dans la bibliothèque
void addLivre(Bibliotheque& bibliotheque) {
    cleanEcran();
    logo(bibliotheque);
    Livre nouveauLivre;
    string ligne;
    cout << "\nLivre\n---------------------------------------------------" << endl;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Nettoyer le flux d'entrée
    cout << "isbn > "; 
    getline(cin, nouveauLivre.isbn);
    cout << "titre > "; 
    getline(cin, nouveauLivre.titre);
    cout << "langue > "; 
    getline(cin, nouveauLivre.langue);

    cout << "Auteurs (ligne vide pour finir) >" << endl;
    while (true) {
        getline(cin, ligne);
        if (ligne.empty()) {
            if (nouveauLivre.auteurs.empty()) {
                cout << ">> Il faut au moins un auteur !" << endl;
                continue;
            }
            break;
        }
        nouveauLivre.auteurs.push_back(ligne);
    }

    bool dateV = false;
    // Boucle jusqu'à obtenir une date valide
    while (!dateV) {
        cout << "Date de parution > ";
        string sDate;
        getline(cin, sDate);

        stringstream flux(sDate);
        char separateur;
        int j, m, a;
        
        //on extrait jour, mois, année
        if (flux >> j >> separateur >> m >> separateur >> a) {
            if (dateValide(j, m, a)) {
                nouveauLivre.dateParution = {j, m, a};
                dateV = true;
            } else {
                cout << "> Date invalide." << endl;
            }
        } else {
            cout << "> Format invalide." << endl;
        }
    }

    cout << "Description (ligne vide pour finir) >" << endl;
    string descriptionComplete = "";
    while (true) {
        getline(cin, ligne);
        if (ligne.empty()){
            break;
        }
        if (!descriptionComplete.empty()){
            descriptionComplete += "\n";
        }
        descriptionComplete += ligne; 
    }
    nouveauLivre.descriptionLivre = descriptionComplete;

    cout << "Genre littéraire > ";
    getline(cin, nouveauLivre.genre);

    bibliotheque.livres.push_back(nouveauLivre);
}

// fonctions d'affichage d'un livre
void printDetailLivre(const Bibliotheque& bibliotheque, const Livre& livre) {
    cleanEcran();
    logo(bibliotheque);
    cout << "Titre : " << livre.titre << " ( " << livre.isbn << " )" << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "\tAuteurs  : ";
    //parcours des auteurs les afficher
    for (size_t i = 0; i < livre.auteurs.size(); ++i) {
        cout << livre.auteurs[i];
        if (i < livre.auteurs.size() - 1){
            cout << ", ";
        } 
    }
    cout << endl;
    cout << "\tLangue   : " << livre.langue << endl; // Affichage de la langue
    cout << "\tParution : " << livre.dateParution.jour << "/"<< livre.dateParution.mois << "/" << livre.dateParution.annee << endl;
    cout << "\tGenre    : " << livre.genre << endl;

    cout << " Description :" << endl;
    cout << " " << livre.descriptionLivre << endl;
    sortie();
}
// fonction d'affichage paginée des livres
void printLivre(const Bibliotheque& bibliotheque) {
    cleanEcran();
    logo(bibliotheque);
    // si la bibliothèque est vide
    if (bibliotheque.livres.empty()) {
        cout << "Aucun livre dans la bibliothèque." << endl;
        sortie();
        return;
    }

    int pageActuelle = 0;
    // si le nombre de livres par page est défini dans la bibliothèque on l'utilise sinon on met 10 par défaut
    int nbrLivreParPage = (bibliotheque.nbrLivreParPage > 0) ? bibliotheque.nbrLivreParPage : 10;
    
    int toucheSuivant = nbrLivreParPage + 1;
    int touchePrecedent = nbrLivreParPage + 2;

    bool resterSurListe = true;

    // tant que l'utilisateur veut rester sur la liste des livres on affiche la page courante et on gère les entrées
    while (resterSurListe) {
        int nbrLivre = bibliotheque.livres.size();
        int totalPages = (nbrLivre + nbrLivreParPage - 1) / nbrLivreParPage;
        int debut = pageActuelle * nbrLivreParPage;
        int fin = min(debut + nbrLivreParPage, nbrLivre);

        // En-tête
        cout << bibliotheque.titre << endl;
        cout << bibliotheque.descriptionBiblio << "\n" << endl;
        cout << "\t Nombre de livres : " << nbrLivre << "\n" << endl;
        cout << "Références :" << endl;
        cout << "---------------------------------------------------\n" << endl;
        // pour chaque livre de la page courante on affiche son numéro visuel, son titre, son ISBN, son genre et sa date de parution
        for (int i = debut; i < fin; ++i) {
            int livreNum = (i - debut) + 1;
            cout << livreNum << ". " << bibliotheque.livres[i].titre << endl;
            cout << "\t" << bibliotheque.livres[i].isbn << " | " << bibliotheque.livres[i].genre << " | Parution : " << bibliotheque.livres[i].dateParution.jour << "/" << bibliotheque.livres[i].dateParution.mois << "/" << bibliotheque.livres[i].dateParution.annee << "\n" << endl;
        }
        // si la page actuelle n'est pas la dernière on affiche l'option pour aller à la page suivante
        if (pageActuelle < totalPages - 1){
            cout << toucheSuivant << ". Page suivante" << endl;
        } 
        // si la page actuelle n'est pas la première on affiche l'option pour aller à la page précédente
        if (pageActuelle > 0){
            cout << touchePrecedent << ". Page precedente" << endl;
        } 
        
        cout << nbrLivre + 1 << ". Retour" << endl;
        
        cout << "\n > Votre choix : ";

        int choix;
        // si l'utilisateur fait une saisie valide on traite son choix
        if (cin >> choix) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            int nbLivresSurCettePage = fin - debut;
            // si le choix est un numéro de livre valide on affiche les détails du livre choisi
            if (choix >= 1 && choix <= nbLivresSurCettePage) {
                int vraiIndex = debut + (choix - 1);
                printDetailLivre(bibliotheque, bibliotheque.livres[vraiIndex]);
            }
            //si non si le choix est la touche suivante et qu'on n'est pas à la dernière page on incrémente la page actuelle
            else if (choix == toucheSuivant && pageActuelle < totalPages - 1) {
                pageActuelle++;
            }
            //si non si le choix est la touche précédente et qu'on n'est pas à la première page on décrémente la page actuelle
            else if (choix == touchePrecedent && pageActuelle > 0) {
                pageActuelle--;
            }
            //si non si le choix est le retour on quitte la boucle
            else if (choix == nbrLivre + 1) {
                resterSurListe = false;
            }
            // si non on affiche un message de choix invalide
            else {
                cout << "Choix invalide." << endl;
                sortie();
            }
        } else {
            // si non saisie invalide on nettoie le flux d'entrée et on affiche un message de saisie invalide
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Saisie invalide." << endl; 
            sortie();
        }
    }
}

// fonction pour mettre une chaîne en minuscules
string enminuscule(string texte) {
    string resultat = texte;
    for (char &c : resultat) {
        c = tolower(c);
    }
    return resultat;
}

// fonction pour rechercher des livres
void searchLivres(const Bibliotheque& bibliotheque) {
    cout << "Rechercher une reference" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "1. Recherche par ISBN-13 " << endl;
    cout << "2. Recherche par numéro d'éditeur" << endl;
    cout << "3. Recherche par Titre " << endl; 
    cout << "> votre choix : "; 
    
    int choix;
    if (!(cin >> choix)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return; 
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string message = "";
    if (choix == 1){
        message = "par ISBN-13";
    } else if (choix == 2) {
        message = "par numéro d'éditeur";
    } else if (choix == 3) {
        message = "par Titre";
    }else {
        cout << "Choix invalide." << endl;
        sortie();
        return;
    }

    cleanEcran();
    logo(bibliotheque);
    
    string termeRecherche;
    cout << "> " << message << ": "; 
    getline(cin, termeRecherche);

    if (termeRecherche.empty()) {
        cleanEcran();
        logo(bibliotheque);
        cout << "Le terme de recherche ne peut pas être vide." << endl;
        sortie();
        return;
    }
    Bibliotheque resultats;
    resultats.titre = " > Résultats de la recherche : " + termeRecherche;
    resultats.nbrLivreParPage = bibliotheque.nbrLivreParPage; 
    resultats.logo = bibliotheque.logo;

    string termeMinuscule = enminuscule(termeRecherche);

    for (const Livre& livre : bibliotheque.livres) {
        bool trouve = false;
        // si l'utilisateur choisir par ISBN ou par Editeur
        if (choix == 1 || choix == 2) {
            if (livre.isbn.find(termeRecherche) != string::npos){
                trouve = true;
            } 
        } 
        //si non si l'utilisateur choisir 3 on convertit le titre en minuscule et on cherche
        else if (choix == 3) {
            string titreMin = enminuscule(livre.titre);
            if (titreMin.find(termeMinuscule) != string::npos) trouve = true;
        }

        if (trouve){
            resultats.livres.push_back(livre);
        } 
    }
    // si aucun livre trouvé on affiche un message et on fait une pause
    if (resultats.livres.empty()) {
        cout << "\n>> Aucun livre trouvé." << endl;
        sortie();
    } else {
        printLivre(resultats);
    }
}
// Fonction pour découper une ligne CSV en champs, en gérant les guillemets et les points-virgules 
vector<string> splitLigneCsv(string ligne) {
    vector<string> champs;
    string champActuel;
    bool dansGuillemets = false;
 
    for (char c : ligne) {
        if (c == '"') {
            dansGuillemets = !dansGuillemets; // basculer l'état des guillemets
        } else if (c == ';' && !dansGuillemets) { // si on rencontre un point-virgule en dehors des guillemets, c'est la fin d'un champ
            champs.push_back(champActuel);// ajouter le champ à la liste
            champActuel = ""; // réinitialiser pour le prochain champ
        } else {
            champActuel += c;
        }
    }
    champs.push_back(champActuel); 
    return champs;
}

// fonction pour importer des livres depuis un fichier CSV
void importLiveCsv(Bibliotheque& bibliotheque) {
    cleanEcran();
    logo(bibliotheque);
    cout << "> chemin vers le fichier d'import : ";

    string nomFichier;
    cin.ignore();
    getline(cin, nomFichier);

    ifstream fichier(nomFichier); // Ouvrir le fichier en lecture
    if (!fichier.is_open()) {
        cout << "Impossible d'ouvrir le fichier '" << nomFichier << "'" << endl;
        sortie();
        return;
    }

    string ligne;
    getline(fichier, ligne); // on saute la première ligne d'en-tête

    int nbLivresAjoutes = 0;
    // Lecture ligne par ligne du fichier CSV
    while (getline(fichier, ligne)) {
        // gestion des guillemets 
        int nbGuillemets = 0;
        for (char c : ligne) {
            if (c == '"') nbGuillemets++;
        }
        // Tant que le nombre de guillemets est impair la phrase n'est pas finie
        while (nbGuillemets % 2 != 0) {
            string suite;
            if (!getline(fichier, suite)) {
                break; 
            }
            ligne += "\n" + suite; // on ajoute la suite à la ligne courante
            // on recompte les guillemets
            for (char c : suite){
                if (c == '"'){
                    nbGuillemets++;
                } 
            } 
        }
        // vector pour stocker les champs découpés
        vector<string> donneescsv = splitLigneCsv(ligne);
        // si le nombre de champs est inférieur à 7 on passe à la ligne suivante
        if (donneescsv.size() < 7){
            continue; 
        }
        // création d'un nouveau livre et remplissage de ses champs
        Livre livre;
        livre.isbn = donneescsv[0];
        livre.titre = donneescsv[1];
        livre.langue = donneescsv[2];

        stringstream fluxAuteurs(donneescsv[3]); // transformer la chaîne en flux pour découper les auteurs
        string unAuteur;
        // découpage des auteurs à la virgule
        while (getline(fluxAuteurs, unAuteur, ',')) {
            livre.auteurs.push_back(unAuteur); // ajout de chaque auteur a la liste des auteurs du livre
        }

        stringstream fluxDate(donneescsv[4]); 
        char tiret; 
        // si on peut extraire jour, mois, année on les stocke dans la structure Date du livre
        if (fluxDate >> livre.dateParution.annee >> tiret >> livre.dateParution.mois >> tiret >> livre.dateParution.jour) {
            // Conversion réussie
        } else {
            // sinon on met une date par défaut 0/0/0
            livre.dateParution = {0, 0, 0}; // Date de parution par défaut
        }
       
        string resume = donneescsv[5];
        // Si le résumé commence et se termine par des guillemets, on les enlève
        if (resume.size() >= 2 && resume.front() == '"' && resume.back() == '"') {
            resume = resume.substr(1, resume.size() - 2);
        }
        livre.descriptionLivre = resume; // Ajout de la description du livre depuis le CSV

        livre.genre = donneescsv[6]; // Ajout du genre du livre depuis le CSV

        bibliotheque.livres.push_back(livre); // ajout du livre à la bibliothèque
        nbLivresAjoutes++; // Incrémentation du compteur de livres ajoutés
    }

    fichier.close(); // Fermeture du fichier après la lecture
    cout << "\n" << nbLivresAjoutes << " référence(s) importée(s)." << endl;
    sortie();
}


// fonction pour gérer le menu des paramètres
void modifierParam(Bibliotheque& bibliotheque) {
    bool resterDansParametres = true;
    while (resterDansParametres) {
        cleanEcran();
        logo(bibliotheque);
        
        cout << "Paramètres" << endl;
        cout << "----------------------------------------------------------------------" << endl;
        cout << "1. Modifier le titre" << endl;
        cout << "2. Modifier la description" << endl;
        cout << "3. Nombre de référence par page" << endl;
        cout << "4. Modifier le logo de l'application" << endl;
        cout << "5. Retour à l'accueil" << endl;
        
        cout << "\nVotre choix : ";
        int choix;
        
        // si le choix n'est pas dans les nombres du menu on recommence la boucle
        if (!(cin >> choix)) {
            cin.clear(); // On netoie cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // On vide le la memoire de cin
            continue; // On recommence la boucle
        }

        // si le choix est 1, on modifie le titre
        if (choix == 1) {
            cleanEcran();
            logo(bibliotheque);
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // On nettoie ICI avant getline
            cout << "\n> Entrez le nouveau titre : ";
            string t;
            getline(cin, t);
            if (!t.empty()){
                bibliotheque.titre = t;
            } 
            sortie();
        }
        //si non si le choix est 2, on modifie la description
        else if (choix == 2) {
            cleanEcran();
            logo(bibliotheque);
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // On nettoie ICI avant getline
            cout << "\n> Entrez la nouvelle description : ";
            string d;
            getline(cin, d);
            if (!d.empty()){
                bibliotheque.descriptionBiblio = d;
            }
            sortie();
        }
        // si non si le choix est 3, on modifie le nombre de références par page
        else if (choix == 3) {
            cleanEcran();
            logo(bibliotheque);
            cout << "\n> Nombre de références par page : "<< endl;
            cout << "> Entrez de références par page (10) : ";
            int n;
            cin >> n;
            if (n > 0){
                bibliotheque.nbrLivreParPage = n;
            } 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sortie();
        }
        //si non si le choix est 4 on modifie le logo
        else if (choix == 4) {
            cleanEcran();
            logo(bibliotheque);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n> Modifier le logo de l'application :" << endl;
            vector<string> nouveauLogo;
            string ligne;
            while (true) {
                getline(cin, ligne);
                if (ligne.empty()) break;
                nouveauLogo.push_back(ligne);
            }
            if (!nouveauLogo.empty()) {
                bibliotheque.logo = nouveauLogo;
            } else {
                cout << "Erreur lors de la modification du logo." << endl;
            }
            sortie();
        }
        // si non si le choix est 5, on retourne à l'accueil
        else if (choix == 5) {
            resterDansParametres = false;
        }
    }
}
// Remplace les \n par des tirets - pour que ça tienne sur une ligne
string tiret_entrer(string texte) {
    for (size_t i = 0; i < texte.length(); i++) {
        if (texte[i] == '\n'){
            texte[i] = '-';
        }
    }
    return texte;
}

// fonctions de sauvegarde et chargement de la bibliothèque
void saveBibliotheque(const Bibliotheque& bibliotheque) {
    ofstream fichierLib("library.db"); // on ouvre le fichier en écriture
    // si on n'arrive pas à ouvrir le fichier on affiche un message d'erreur et on quitte
    if (!fichierLib.is_open()) {
        cout << "Erreur sauvegarde !" << endl;
        return;
    }
    fichierLib << bibliotheque.titre << endl;
    fichierLib << tiret_entrer(bibliotheque.descriptionBiblio) << endl; // on encode la description pour gérer les sauts de ligne
    fichierLib << bibliotheque.logo.size() << endl; 
    for (const string& ligne : bibliotheque.logo) fichierLib << ligne << endl;
    fichierLib << bibliotheque.livres.size() << endl; 
    // pour chaque livre on écrit ses champs dans le fichier
    for (const Livre& l : bibliotheque.livres) {
        fichierLib << l.isbn << endl;
        fichierLib << l.titre << endl;
        fichierLib << l.langue << endl;
        // pour les auteurs on les écrit séparés par des virgules
        for (size_t i=0; i<l.auteurs.size(); ++i) {
            fichierLib << l.auteurs[i] << (i < l.auteurs.size()-1 ? "," : "");
        }
        fichierLib << endl;
        fichierLib << l.dateParution.jour << " " << l.dateParution.mois << " " << l.dateParution.annee << endl;
        fichierLib << l.genre << endl;
        fichierLib << tiret_entrer(l.descriptionLivre) << endl;
    }
    fichierLib.close(); // fermeture du fichier
}

// L'inverse : Remplace les tirets - par des vrais  \n
string entrer_tiret(string texte) {
    for (size_t i = 0; i < texte.length(); i++) {
        if (texte[i] == '-'){
            texte[i] = '\n';
        }
    }
    return texte;
}
// Retourne true si la bibliothèque a été chargée, false sinon
bool chargerBibliotheque(Bibliotheque& bibliotheque) {
    ifstream fichierLib("library.db"); 
    if (!fichierLib.is_open()) {
        return false;
    } 

    string ligne;
    // on arrive pas à lire le titre on retourne false
    if (!getline(fichierLib, bibliotheque.titre)){
        return false;
    }
    getline(fichierLib, ligne);
    bibliotheque.descriptionBiblio = entrer_tiret(ligne); // on décode la description pour rétablir les sauts de ligne
    int nbLignesLogo;
    fichierLib >> nbLignesLogo;
    fichierLib.ignore();
    bibliotheque.logo.clear();
    for(int i=0; i<nbLignesLogo; ++i) {
        getline(fichierLib, ligne);
        bibliotheque.logo.push_back(ligne);
    }

    int nbLivres;
    fichierLib >> nbLivres;
    fichierLib.ignore(); 
    
    bibliotheque.livres.clear();
    for(int i=0; i<nbLivres; ++i) {
        Livre livre; // création d'un livre temporaire pour le remplir
        getline(fichierLib, livre.isbn);
        getline(fichierLib, livre.titre);
        getline(fichierLib, livre.langue);

        string ligneAuteurs;
        getline(fichierLib, ligneAuteurs); 
        stringstream flux(ligneAuteurs); // Pour couper les auteurs à la virgule
        string unAuteur;
        while(getline(flux, unAuteur, ',')){
            livre.auteurs.push_back(unAuteur); // ajout de chaque auteur à la liste des auteurs du livre
        }
        fichierLib >> livre.dateParution.jour >> livre.dateParution.mois >> livre.dateParution.annee;
        fichierLib.ignore();

        getline(fichierLib, livre.genre);
        getline(fichierLib, ligne);
        livre.descriptionLivre = entrer_tiret(ligne); // Décodage de la description via les - pour retablir les sauts de ligne

        bibliotheque.livres.push_back(livre); // ajout du livre à la bibliothèque
    }
    return true;
}
// fonction qui supprime toutes les références
void deletAllRefLivre(Bibliotheque& bibliotheque) {
    bibliotheque.livres.clear();
}
// Fonction pour préparer un titre en vue du tri (ignorer les articles et mettre en majuscule)
string prefixeTitre(string titre) {
    string t = titre;
    //convertir tout les caractères du titre en majuscules
    for (char &c : t){
        c = toupper(c);
    }
    // vecteurs de prefixe a ignorer
    vector<string> prefixes = {"Le", "La", "L'","l" ,"Un", "J'", "D'", "Qu'", "S'", "Les","À la", "Des", "Aux", "Au", "À l'", "Aux", "Du", "De là", "De l'", "De", "Mes", "Tes", "Ses", "Nos", "Vos", "Leur", "Lui", "Elle", "Il", "Ils", "Elles", "À la", "À l'", "À"};
    //pour chaque préfixe on vérifie si le titre commence par un de ces prefixes
    for (const string& p : prefixes) {
        if (t.substr(0, p.size()) == p) {
            return t.substr(p.size());
        }
    }
    return t;
}

//Fonction qui compare deux livres en fonction de leur titre pour le tri et retourne true si le titre du premier livre est inférieur à celui du second
bool comparLivres(const Livre& a, const Livre& b) {
    return prefixeTitre(a.titre) < prefixeTitre(b.titre); // retourne true si le titre de a est inféferieur a celui de b
}

// fontion pour exporter la bibliotheque en html
void exporterHTML(const Bibliotheque& bibliotheque) {
    cleanEcran();
    logo(bibliotheque);
    // si la bibliotheque est vide on affiche un message et on fait une pause
    if (bibliotheque.livres.empty()) {
        cout << "La bibliothèque est vide." << endl;
        sortie();
        return;
    }
    // on crée une copie des livres pour les trier sans modifier l'ordre dans la bibliothèque
    vector<Livre> livresTries = bibliotheque.livres;
    // on trie les livres par titre
    sort(livresTries.begin(), livresTries.end(), comparLivres);

    // tableau de booléens pour noter les lettres qu'on a trouvées.
    bool lettrePresente[256] = {false}; 

    // pour chaque livre on regarde la première lettre de son titre trié
    for (size_t i = 0; i < livresTries.size(); i++) {
        
        Livre livreCourant = livresTries[i];
        string titreNettoye = prefixeTitre(livreCourant.titre);
        char premiereLettre = titreNettoye[0];
        if (isdigit(premiereLettre)) {
            lettrePresente['#'] = true;
        } 
        else {
            int ancreLivre = (int)premiereLettre;
            lettrePresente[ancreLivre] = true;
        }
    }

    // creation du fichier .html
    string nomFichier = "bibliotheque.html";
    // ouverture du fichier en écriture
    ofstream fichierHtml(nomFichier);
    // si on ne peut pas ouvrir le fichier on affiche un message d'erreur et on quitte
    if (!fichierHtml.is_open()) {
        cout << "Erreur création fichier." << endl;
        return;
    }

    // En-tête  HTML et CSS combiner
    fichierHtml << "<!DOCTYPE html><html lang='fr'><head><meta charset='UTF-8'>" << endl;
    fichierHtml << "<title>" << bibliotheque.titre << "</title>" << endl;
    fichierHtml << "<style>" << endl;
    
    // mise en page du body
    fichierHtml << "body { font-family: sans-serif; padding: 20px; background-color: white; color: #333; text-align: center; }" << endl;
    
    // style des titres
    fichierHtml << "h1 { margin-bottom: 40px; color: #444; }" << endl;

    // mise en pages de ancreLivre de A a Z
    fichierHtml << ".ancreLivre { margin-bottom: 50px; padding: 10px; }" << endl;
    fichierHtml << ".ancreLivre a { margin: 0 5px; text-decoration: none; color: #007bff; font-weight: bold; font-size: 1.1em; }" << endl;
    fichierHtml << ".ancreLivre a:hover { text-decoration: underline; }" << endl;
    fichierHtml << ".ancreLivre span { margin: 0 5px; color: #ddd; font-weight: bold; font-size: 1.1em; cursor: default; }" << endl;
    
    // classe section-lettre pour les sections de chaque lettre
    fichierHtml << ".section-lettre { width: 80%; margin: 40px auto 10px auto; color: #888; font-size: 2em; border-bottom: 2px solid #eee; text-align: left; }" << endl;

    // class livre pour chaque livre
    fichierHtml << ".livre { " << endl;
    fichierHtml << "  width: 80%; " << endl;          
    fichierHtml << "  margin: 0 auto; " << endl;      
    fichierHtml << "  padding: 12px 0; " << endl;     
    fichierHtml << "  border-bottom: 1px solid #eee; " << endl; 
    fichierHtml << "  text-align: left; " << endl;
    fichierHtml << "}" << endl;
    // Style du titre du livre
    fichierHtml << ".livre h3 { margin: 0; font-size: 1em; color: #000; }" << endl;
    fichierHtml << ".livre span { color: #555; }" << endl; // Couleur gris foncé pour ISBN/Auteur
    fichierHtml << "</style></head><body>" << endl;
    // Titre de la bibliothèque
    fichierHtml << "<h1>" << bibliotheque.titre << "</h1>" << endl;

    fichierHtml << "<div class='ancreLivre'>" << endl;
    // si on a au moins un livre qui commence par un chiffre on crée un lien vers la section # on met une ancre
    if (lettrePresente['#']){
        fichierHtml << "<a href='#chiffre'>#</a>";
    }else{
        fichierHtml << "<span>#</span>";
    } 
    // pour chaque lettre de A à Z on vérifie si on a au moins un livre qui commence par cette lettre
    for (char c = 'A'; c <= 'Z'; c++) {
        // convertion en int de la lettre pour accéder à la case du tableau
        int ancreLivre = (int)c;
        // si on a au moins un livre qui commence par cette lettre on crée un lien vers la section de cette lettre
        if (lettrePresente[ancreLivre] == true) {
            fichierHtml << "<a href='#lettre_" << c << "'>" << c << "</a>";
        } 
        else {
            // si non on affiche la lettre en gris clair sans lien
            fichierHtml << "<span>" << c << "</span>";
        }
    }
    fichierHtml << "</div>" << endl;

    
    char derniereLettre = 0;
    // pour chaque livre trié on crée une section si la première lettre du titre change
    for (const Livre& livre : livresTries) {
        string t = prefixeTitre(livre.titre);
        // si la première lettre du titre est vide on passe au suivant
        if (t.empty()){
            continue; 
        }
        char c = t[0]; // pour chaque livre on prend la première lettre du titre
        string ancreID;
        // si la première lettre est un chiffre on crée une ancre spéciale pour les chiffres
        if (isdigit(c)) { 
            c = '#'; 
            ancreID = "chiffre"; 
        }
        else { // si non on met la lettre en majuscule pour l'ancre
            c = toupper(c);
            ancreID = "lettre_";
            ancreID += c; 
        }
        // si la lettre courante est différente de la dernière lettre on crée une nouvelle section
        if (c != derniereLettre) {
            fichierHtml << "<h2 id='" << ancreID << "' class='section-lettre'>" << c << "</h2>" << endl;
            derniereLettre = c;
        }
        fichierHtml << "<div class='livre'>" << endl;
        fichierHtml << "<h3>" << livre.titre;
        fichierHtml << " <span style='font-weight:normal'> - " << livre.isbn << " - ";
        fichierHtml << "<i>";
        // on affiche les auteurs séparés par des virgules
        for(size_t i=0; i<livre.auteurs.size(); ++i) {
            fichierHtml << livre.auteurs[i] << (i < livre.auteurs.size()-1 ? ", " : "");
        }
        fichierHtml << "</i>";
        fichierHtml << "</span></h3>" << endl;
        fichierHtml << "</div>" << endl;
    }

    fichierHtml << "</body></html>" << endl;
    fichierHtml.close();
    
    cout << "Export effectué " << endl;
    sortie();
}
