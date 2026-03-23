# Projet de Bibliothèque en C

Ce projet est une application de gestion de bibliothèque développée en langage C. Il permet de gérer les livres, les adhérents et les prêts.

## 🚀 Fonctionnalités

### 📚 Gestion des Livres
- Ajouter un nouveau livre
- Afficher tous les livres
- Rechercher un livre par titre ou auteur
- Modifier les informations d'un livre
- Supprimer un livre

### 👥 Gestion des Adhérents
- Ajouter un nouvel adhérent
- Afficher tous les adhérents
- Rechercher un adhérent par nom ou numéro d'adhérent
- Modifier les informations d'un adhérent
- Supprimer un adhérent

### 🔄 Gestion des Prêts
- Enregistrer un prêt
- Retourner un livre
- Afficher tous les prêts
- Afficher les prêts en cours
- Afficher l'historique des prêts

## 🛠️ Installation

### Prérequis
- Un compilateur C (GCC recommandé)
- Make (pour la compilation automatique)

### Compilation
1. Clonez le dépôt :
   ```bash
   git clone <url-du-dépôt>
   cd bibliotheque_c
   ```

2. Compilez le projet :
   ```bash
   make
   ```

## 🏃‍♂️ Utilisation

### Lancement
Après compilation, lancez l'application :
```bash
./bibliotheque
```

### Menu Principal
Le menu principal propose les options suivantes :
```
1. Gestion des Livres
2. Gestion des Adhérents
3. Gestion des Prêts
4. Quitter
```

### Gestion des Livres
```
1. Ajouter un livre
2. Afficher tous les livres
3. Rechercher un livre
4. Modifier un livre
5. Supprimer un livre
6. Retour au menu principal
```

### Gestion des Adhérents
```
1. Ajouter un adhérent
2. Afficher tous les adhérents
3. Rechercher un adhérent
4. Modifier un adhérent
5. Supprimer un adhérent
6. Retour au menu principal
```

### Gestion des Prêts
```
1. Enregistrer un prêt
2. Retourner un livre
3. Afficher tous les prêts
4. Afficher les prêts en cours
5. Afficher l'historique des prêts
6. Retour au menu principal
```

## 📂 Structure du Projet

```
bibliotheque_c/
├── src/
│   ├── main.c             # Point d'entrée de l'application
│   ├── livre.c            # Fonctions de gestion des livres
│   ├── adherent.c         # Fonctions de gestion des adhérents
│   ├── pret.c             # Fonctions de gestion des prêts
│   ├── structures.h       # Définitions des structures de données
│   └── utils.c            # Fonctions utilitaires
├── include/
│   ├── livre.h            # Prototypes des fonctions de gestion des livres
│   ├── adherent.h         # Prototypes des fonctions de gestion des adhérents
│   ├── pret.h             # Prototypes des fonctions de gestion des prêts
│   └── utils.h            # Prototypes des fonctions utilitaires
├── data/
│   ├── livres.dat         # Fichier de sauvegarde des livres
│   ├── adherents.dat      # Fichier de sauvegarde des adhérents
│   └── prets.dat          # Fichier de sauvegarde des prêts
├── Makefile               # Script de compilation
└── README.md              # Ce fichier
```

## 💾 Sauvegarde des Données

Les données sont sauvegardées automatiquement dans les fichiers suivants :
- `data/livres.dat` - Liste des livres
- `data/adherents.dat` - Liste des adhérents
- `data/prets.dat` - Liste des prêts

## 👥 Auteurs

Ce projet a été développé par :
- [Votre Nom 1]
- [Votre Nom 2]

## 📄 Licence

Ce projet est sous licence MIT. Voir le fichier `LICENSE` pour plus de détails.

## 🤝 Contribuer

Les contributions sont les bienvenues ! N'hésitez pas à :
1. Fork le projet
2. Créer une branch pour votre fonctionnalité (`git checkout -b feature/AmazingFeature`)
3. Commit vos changements (`git commit -m 'Add some AmazingFeature'`)
4. Push vers la branch (`git push origin feature/AmazingFeature`)
5. Ouvrir une Pull Request

## 📝 Notes

- Le projet utilise des fichiers binaires pour la persistance des données
- Les structures de données sont définies dans `structures.h`
- Les fonctions utilitaires sont centralisées dans `utils.c`

## 📞 Support

Pour toute question ou problème, veuillez ouvrir une issue.