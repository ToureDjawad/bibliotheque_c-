# Checklist Fonctionnelle - SAE 1.1

## 1. Initialisation et Démarrage

- [x] Au lancement, détecter si la bibliothèque (fichier de données) existe déjà.
- [x] Si la bibliothèque n'existe pas : lancer une procédure de création demandant le titre et la description de la nouvelle bibliothèque.
- [x] Si la bibliothèque existe : charger les données existantes.
- [x] Charger la configuration (logo, préférences) depuis le fichier de configuration.
- [x] Afficher le logo ASCII avant le menu principal.

## 2. Alimentation de la bibliothèque (F02)

_Cette étape est prioritaire pour pouvoir tester l'affichage et la recherche par la suite._

**Ajout manuel (F02.1)**

- [x] Vérifier que l'ISBN-13 saisi n'est pas déjà présent dans la bibliothèque.
- [x] Demander la saisie du Titre (chaîne simple).
- [x] Demander la saisie de la Langue (chaîne simple).
- [x] Demander la saisie des Auteurs (saisie de plusieurs noms, s'arrête sur une ligne vide).
- [x] Demander la saisie de la Description (saisie de plusieurs lignes, s'arrête sur une ligne vide).
- [x] Demander la saisie de la Date de parution et vérifier que le format est valide (jour/mois/année cohérents).
- [x] Demander la saisie du Genre (chaîne simple).

**Importation de masse (F02.2)**

- [x] Demander à l'utilisateur le chemin vers le fichier CSV.
- [x] Ignorer la première ligne du fichier (en-tête).
- [x] Traiter chaque ligne en séparant les champs par le caractère `;`.
- [x] Gérer le cas spécifique du champ "Résumé" qui peut contenir des retours à la ligne et est encadré par des guillemets `"`.
- [x] Ajouter les livres extraits à la bibliothèque courante.

**Suppression (F02.3)**

- [x] Demander une confirmation explicite avant de supprimer toutes les références.
- [x] Retirer l'ensemble des livres de la bibliothèque.

## 3. Consultation et Navigation (F01)

_À tester une fois que des livres ont été ajoutés._

- [x] Afficher une liste paginée résumée (ISBN, Titre, Auteurs) correspondant à la page courante.
- [x] Permettre à l'utilisateur de passer à la page suivante ou précédente.
- [x] Permettre à l'utilisateur de sélectionner un livre dans la liste pour en voir le détail.
- [x] Afficher la fiche détaillée complète d'un livre (toutes les informations saisies en étape 2).

## 4. Recherche de références (F03)

- [x] Permettre la recherche exacte par ISBN-13.
- [x] Permettre la recherche par numéro d'éditeur (partie spécifique de l'ISBN).
- [x] Permettre la recherche par partie du titre (insensible à la casse majuscule/minuscule).
- [x] Afficher les résultats de la recherche sous forme de liste (même présentation que la consultation F01).
- [x] Gérer la pagination des résultats si la recherche retourne plus de livres que la limite par page.
- [x] Permettre d'accéder à la fiche détaillée d'un livre depuis les résultats de recherche.

## 5. Exportation HTML (F04)

- [x] Générer un fichier HTML unique contenant l'ensemble du catalogue.
- [x] Créer un index alphabétique en haut de page (liens ancres).
- [x] Rendre inactifs les liens de l'index qui ne correspondent à aucun livre.
- [x] Trier les livres par ordre alphabétique des titres.
- [x] Appliquer la règle de tri ignorant les articles définis/indéfinis en début de titre (Le, La, L', Un, etc.).
- [x] Grouper les livres par lettre dans le corps de la page.
- [x] Grouper les titres commençant par un chiffre sous une section `#`.

## 6. Paramétrage de l'application (F05)

- [x] Permettre la modification du titre et de la description (conserver l'ancienne valeur si la saisie est vide).
- [x] Permettre la modification du nombre de références affichées par page.
- [x] Permettre la modification du logo ASCII (saisie multilignes terminée par une ligne vide).
- [x] Assurer que ces réglages sont conservés pour le prochain lancement (fichier de configuration).

## 7. Gestion de la fermeture (F06)

- [x] Détecter si des modifications ont été effectuées sur la bibliothèque (ajout, suppression, modification d'infos) depuis la dernière sauvegarde.
- [x] Si aucune modification : fermer l'application immédiatement.
- [x] Si modifications en attente : afficher un menu proposant "Sauvegarder et quitter" ou "Quitter sans sauvegarder".
- [x] Exécuter la sauvegarde des données (fichier bibliothèque) si l'utilisateur le demande.
