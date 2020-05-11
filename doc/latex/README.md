---

title: Exercices cours de Secu sur les clouds
author:

- Clément \textsc{Chavanon}
- Romain \textsc{Hu}
- Romain \textsc{Hubert}
- Maxime \textsc{Grimaud}
- Volodia \textsc{Parol-Guarino}
-

coauthor: "Encadrant : Pascal \\textsc{Garcia}"
date: 2019-2020
biblio-style: plain-fr
bibliography: references
...

# Introduction {.unnumbered}

## Le jeu des pingouins

Le jeu des pingouins est un jeu de stratégie sur plateau de 4 joueurs. Le plateau contient 60 cases hexagonales sur lesquelles se trouvent 1 à 3 poissons.

En début de partie, chaque joueur place un certain nombre de pingouins (de 2 à 4 suivant le nombre de joueurs) sur le plateau. A chaque tour, le joueur doit, si possible, bouger l'un de ses pingouins. Les mouvements de ceux se font sur en ligne droite depuis les 6 faces de la case hexagonale sur laquelle il se trouve. Il ne peut passer par des trous ou au-dessus d'autres pingouins, peu importe leur couleur. Une fois le mouvement achevé, la case de départ est retiré du plateau. Le joueur peut alors incrémenter du nombre de poisson qu'il y avait sur cette case son score.

Le jeu se termine lorsque plus aucun pingouins ne peut se déplacer. Le joueur avec le plus de points (poissons) remporte la partie.

## Notre tâche

### Au départ

Le sujet portait sur l'implémentation de ce jeu dans un environnement Web, en utilisant le nouveau standard _WebAssembly_. Les sources du projet sont compilés avec _Emscripten_ qui permet de coder en `c++` pour la partie technique. L'interface devait se faire avec les libraires _Simple DirectMedia Layer_.

### Bref suivi

Afin de tester la faisabilité et les différentes technologies, nous avons décidé de procéder à la création de l'algorithme de façon abstraite et de tester avec un jeu simple et facilement implémentable : le morpion. Pour la partie graphique nous avions simplement codé en JavaScript vanilla. En parallèle nous avons testé une autre technologie pour cela : `PixiJS`. Cependant cela ne s'est pas avéré satisfaisant pour notre utilisation et avons décidé de choisir quelque chose de plus simple : `angular`.

### Nos prédécesseurs

Ce projet n'est pas nouveau. Une précédente équipe y a déjà passé de nombreuses heures. Cependant, afin de simplifier notre travail il a été décidé de tout refaire, y compris le MCTS dont le code leur avait été donné déjà optimisé. En effet, notre technologie étant récente, le _multithreading_ par exemple pouvait s'avérer plus compliqué à porter en _WebAssembly_ qu'à réécrire.

### Notre objectif

Principalement nous nous sommes concentré sur le fonctionnement correct de tout le projet et pas seulement de l'algorithme et du jeu. C'est pour cela que nous avons choisi de présenter un résultat plus correct qu'optimal (par exemple nous n'avons pas utilisé de représentation en _bitboards_, comme l'on fait nos prédécesseurs, de même qu'ils n'ont pas eu l'algorithme à gérer).

# Réalisation

## Représentation du jeu

## MCTS

## Multihtreading

## Interface graphique

## _Bindings_ MCTS

# Conclusion
