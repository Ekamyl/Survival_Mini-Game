# ☄️ Survival Mini-Game

Un mini-jeu de survie arcade nerveux développé en **C** avec la bibliothèque **SDL2**. Ce projet propose une expérience immersive unique grâce à une interface simulant un système d'exploitation rétro.

---

## 🕹️ Présentation du Jeu

Le jeu s'ouvre sur une séquence d'initialisation scriptée, simulant le démarrage d'un ordinateur. Une fois le système chargé, une fenêtre de gameplay s'affiche sur un bureau virtuel.

**Le concept :**
Incarnez un personnage dont la survie dépend de vos réflexes. Vous devez esquiver une pluie de boules de feu tombant du ciel de manière aléatoire. Tenez le plus longtemps possible pour battre votre score dans une ambiance visuelle et sonore dynamique.

---

## 🎮 Contrôles

Le jeu se prend en main instantanément avec les commandes suivantes :

* **Déplacements :** Touches directionnelles (**Flèches**) ou **ZQSD** (selon la configuration).
* **Interactions :** La souris est utilisée pour naviguer dans l'interface du "système d'exploitation" au lancement.
* **Quitter :** Touche **Echap** ou fermeture de la fenêtre.

---

## 🛠️ Spécifications Techniques

L'architecture du jeu est modulaire et repose sur les fonctionnalités avancées de la **SDL2** :

* **Interface OS Simulée :** Animations de chargement et fenêtrage interne pour renforcer l'immersion.
* **Gestionnaire d'Événements :** Un *Event Manager* centralisé traite les entrées clavier et souris en temps réel.
* **Moteur d'Animation :** Utilisation de *spritesheets* avec un compteur de frames interne pour des mouvements fluides.
* **Extensions Multimédia :** Intégration de `SDL2_image`, `SDL2_ttf` (textes) et `SDL2_mixer` (audio).

---

## 📋 Prérequis & Dépendances

Le projet est conçu pour les systèmes de type Unix (Linux/macOS). Les bibliothèques de développement suivantes sont nécessaires :

* **SDL2** (Core), **SDL2_image**, **SDL2_ttf**, **SDL2_mixer**

### Installation des dépendances (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
```

---

## 🚀 Compilation et Exécution

Utilisez le Makefile inclus pour gérer le projet simplement depuis votre terminal :

```bash
# Pour compiler le projet et générer l'exécutable
make

# Pour compiler et lancer le jeu directement
make run

# Pour nettoyer les fichiers objets (.o) et l'exécutable
make clean
```

---

# 📂 Informations sur le Dépôt

Ce dépôt contient la version autonome et finale du mini-jeu.

- Auteur : Ekrem (Ekamyl)

- Dépôt Officiel : https://github.com/Ekamyl/Survival_Mini-Game