#ifndef BIBLIOTHEQUE_HPP
#define BIBLIOTHEQUE_HPP

#include <string>
#include <vector>   

//Structure pour gérer la date
struct Date{
    int jour;
    int mois;
    int annee;
};
// Structure pour représenter un Livre
struct Livre {
    std::string isbn; //identifiant unique
    std::string titre; //Titre du livre
    std::string langue; // langue du livre
    std::vector<std::string> auteurs; // Un livre peut avoir plusieurs auteurs
    std::string descriptionLivre; // Description du livre
    Date dateParution; // Date de parution
    std::string genre; // Genre du livre
};
// Strucure Bibliothèque
struct Bibliotheque {
    std::string titre; // Nom de la bibliothèque
    std::string descriptionBiblio; // Description de la bibliothèque
    std::vector<Livre> livres; // Liste des livres dans la bibliothèque
    std::vector<std::string> logo; // Pour stocker le dessin ASCII
    int nbrLivreParPage;             // Pour stocker le nombre "10" par page
};

// Fonction pour effacer l'écran
void cleanEcran();
// Fonction pause
void sortie();
// fonction pour vérifier la validité d'une date
bool dateValide(int j, int m, int a);
// Fonction pour gérer les références des livres
bool refLivre(Bibliotheque& bibliotheque);
// Fonction pour charger la configuration depuis le fichier app.conf
void chargeAppConf(Bibliotheque& bibliotheque);
// Fonction pour afficher le logo de la bibliothèque
void logo(const Bibliotheque& biblioteque);
// Fonction pour initialiser une bibliothèque avec des valeurs par défaut
void initBibliotheque(Bibliotheque &bibliotheque);
// Fonction pour ajouter un livre à la bibliothèque
void addLivre(Bibliotheque &bibliotheque);
// Affiche le détail complet d'un livre spécifique
void printDetailLivre(const Bibliotheque& bibliotheque, const Livre& livre);
// Affiche la liste des livres dans la bibliothèque
void printLivre(const Bibliotheque& bibliotheque);
// Fonction pour modifier les paramètres de la bibliothèque
void modifierParam(Bibliotheque& bibliotheque);
// Fonction pour découper une ligne CSV en champs, en gérant les guillemets et les points-virgules
std::vector<std::string> splitLigneCsv(std::string ligne);
// Fonction pour importer des livres depuis un fichier CSV
void importLiveCsv(Bibliotheque& bibliotheque);
// fonction pour mettre une chaîne en minuscules
std::string enminuscule(std::string texte);
// Fonction de recherche
void searchLivres(const Bibliotheque& bibliotheque);
// Remplace les "Entrée" (\n) par des tirets (-) pour que ça tienne sur une ligne
std::string tiret_entrer(std::string texte);
// Fonctions de sauvegarde et de chargement de la bibliothèque
void saveBibliotheque(const Bibliotheque& bibliotheque);
// fonction pour remplacer les tirets (-) par des vrais "Entrée" (\n) pour restaurer les sauts de ligne
std::string entrer_tiret(std::string texte);
// Fonction pour charger la bibliothèque depuis le fichier library.db
bool chargerBibliotheque(Bibliotheque& bibliotheque);
// Fonction pour supprimer toutes les références de la bibliothèque
void deletAllRefLivre(Bibliotheque& bibliotheque);
// Fonction pour préparer un titre en vue du tri (ignorer les articles et mettre en majuscule)
std::string prefixeTitre(std::string titre);
// Fonction de comparaison de deux livres pour le tri par titre
bool comparLivres(const Livre& a, const Livre& b);
// Fonction pour exporter la bibliothèque en HTML
void exporterHTML(const Bibliotheque& bibliotheque);

#endif
