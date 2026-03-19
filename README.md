# Dual Pulse 1.0

Jeu de plateforme auto-scrolling développé en **C++ / SFML 3.0** avec un moteur custom.

---

## 🎮 Contrôles

| Touche | Action |
|--------|--------|
| `ESPACE` | Sauter (maintenir = saut continu) |
| `F11` | Basculer plein écran / fenêtré |

---

## 🚀 Lancement

1. Ouvrir la solution dans **Visual Studio 2022** (toolset v143)
2. Compiler en mode Debug ou Release
3. Lancer l'exécutable

> Résolution par défaut : **1280x720** — modifiable via F11 ou le menu Option

---

## 🗂️ Scènes

| Scène | Description |
|-------|-------------|
| **MainMenu** | Menu principal — Jouer, Option, Quitter |
| **Option** | Paramètres du jeu |
| **Powerup** | Sélection d'un pouvoir entre deux runs |
| **Main** | Scène de jeu principale |
| **Game Over** | Écran de mort avec skull animé |
| **Pause** | Écran de pause (en cours) |

---

## ❤️ Système de HP

- Le joueur démarre avec **2 HP**
- À chaque collision mortelle, il perd **1 HP**
- Après une collision, un **flash d'invincibilité** s'active automatiquement (clignotement)
- À **0 HP** → écran Game Over
- Les HP s'affichent en **rouge en haut à gauche** de l'écran (ex: `HP: 2/2`)

---

## ⚡ Powerups

À la fin de chaque run, le joueur choisit **1 powerup** parmi 2 proposés.

| Powerup | Effet | Durée |
|---------|-------|-------|
| **+1 Vie** | Augmente les HP max ET les HP actuels de 1 | Permanent (run) |
| **Invincibilité** | S'active à la première collision mortelle — ignore les dégâts | 3 secondes |

> Le powerup **Invincibilité** se consomme à la première collision. Pendant 3 secondes, toutes les collisions sont ignorées et le joueur clignote.

---

## ⚙️ Menu Option

| Paramètre | Description |
|-----------|-------------|
| **Plein écran** | Toggle ON/OFF via bouton ou `F11` |
| **Volume son** | Ajustable de 0% à 100% par paliers de 10% avec les boutons `+` / `-` |
| **Touche saut** | `ESPACE` (reconfigurable prévu) |
---

## 🗺️ Niveaux

- Générés **procéduralement** à partir de fichiers `.txt`
- Chaque run = **9 segments** choisis aléatoirement parmi 5 variantes
- Vitesse de défilement : **500 pixels/seconde**

### Éléments du niveau

| Valeur | Élément | Effet |
|--------|---------|-------|
| `0` | Vide | — |
| `1` | Bloc | Sol si dessus, mort si collision latérale |
| `2` | Spike | Mort instantanée |
| `3` | Orbe | Permet de sauter depuis les airs |

---

## 🏗️ Architecture technique

### Stack
- **Langage** : C++17
- **Moteur graphique** : SFML 3.0
- **IDE** : Visual Studio 2022 (toolset v143)
- **FPS cible** : 60 (setFramerateLimit)

### Moteur (Engine)
| Classe | Rôle |
|--------|------|
| `Engine` | Singleton, point d'entrée global |
| `SceneModule` | Fenêtre SFML, boucle principale, plein écran |
| `Scene` | Conteneur de GameObjects |
| `GameObject` | Entité composée de Components |
| `InputManager` | Clavier, clics, hover |
| `Event` | Événements récurrents (id négatif = permanent) |

### Jeu
| Classe | Rôle |
|--------|------|
| `Scenes` | Factory de toutes les scènes |
| `Settings` | Singleton — plein écran, volume |
| `PlayerState` | Singleton — HP, powerup actif, invincibilité |
| `Gen` / `Level` | Génération et défilement des niveaux |
| `Elements` | Factory des objets du niveau |

### Callbacks moteur / jeu
| Callback | Déclencheur |
|----------|-------------|
| `onFullscreenToggle` | Touche F11 |
| `onFullscreenApplied` | Après recréation de la fenêtre |
| `onLevelComplete` | Fin du run (tous les blocs sortis) |

---

## 📁 Structure des assets

```
Asset/
├── Font/
│   └── Moonstrike.ttf
├── Boutton/
│   └── p_button.png
├── GameOver/
│   ├── background.png
│   ├── skull.png
│   └── harold-screamer.mp3
├── background/
│   └── bg.png
└── player.png

Assets/
└── {index}{variante}.txt   (ex: 03.txt — segments de niveau)
```

---

## 🐛 Notes connues

- La scène **Pause** est en cours d'implémentation
- Le **rebind de touches** est prévu mais pas encore implémenté
- Le **Double Saut** est défini dans `PowerupType` mais pas encore implémenté
