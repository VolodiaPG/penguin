---
title: Jeu des pingouins à base de MCTS (_Monte Carlo Tree Search_) sur le navigateur en utilisant le format _WebAssembly_
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

"Pingouins" est un jeu de stratégie et de plateau sur lequel s'affrontent 2 à 4 joueurs. Le plateau contient 60 cases hexagonales qui comportent 1 à 3 poissons.

En début de partie, chaque joueur place un certain nombre de pingouins (de 2 à 4 suivant le nombre de joueurs) sur le plateau. A chaque tour, le joueur doit, si possible, bouger l'un de ses pingouins. Les déplacements autorisés se font en ligne droite suivant les 6 faces de la case hexagonale sur laquelle se trouve le pingouin. Il ne peut passer par-dessus des trous ou au-dessus d'autres pingouins, peu importe qu'ils appartiennent ou non au même joueur. Une fois le mouvement achevé, la case de départ est retirée du plateau. Le joueur peut alors incrémenter son score du nombre de poissons qu'il y avait sur cette case. Si un pingouin ne peut plus se déplacer, le joueur retire ce dernier ainsi que la case sur laquelle il était. Dans ce cas-là, le joueur remporte aussi les poissons contenus dans cette case.

Le jeu se termine lorsque plus aucun pingouin ne peut se déplacer. Le joueur avec le plus de points (poissons) remporte la partie.

## Notre tâche

### Sujet

Le sujet portait sur l'implémentation de ce jeu dans un environnement Web, en utilisant le nouveau standard `WebAssembly`. Les sources du projet sont compilées avec `Emscripten` qui permet de coder en `C++` pour la partie technique. L'interface devait se faire avec les bibliothèques _Simple DirectMedia Layer_.

### Récapitulatif

Afin de tester la faisabilité et les différentes technologies, nous avons décidé de procéder à la création de l'algorithme de façon abstraite et de tester avec un jeu simple et facilement implémentable : le morpion. Pour la partie graphique nous avions simplement codé en JavaScript pur. Pour la suite du projet, pour faciliter le développement de la partie front-end, nous avons décidé de choisir : `Angular`. Sur la preuve de concept nous avions testé une autre technologie pour gérer le graphisme du jeu : `PixiJS`. Cependant, plus tard, cela ne s'est pas avéré satisfaisant pour notre utilisation. En effet `PixiJS` nécessite une gestion asynchrone de son canvas, son intégration dans une application `Angular` doit donc se faire dans une zone indépendante, le _binding_ avec le `WebAssembly` devenait alors trop complexe. 

### Nos prédécesseurs

Ce projet n'est pas nouveau. Une précédente équipe y a déjà passé de nombreuses heures. Cependant, afin de simplifier notre travail il a été décidé de tout refaire, y compris le MCTS dont le code leur avait été donné déjà optimisé. En effet, notre technologie étant récente, le _multithreading_ par exemple pouvait s'avérer plus compliqué à porter en `WebAssembly` qu'à réécrire.

### Notre objectif

Principalement nous nous sommes concentrés sur le fonctionnement correct de tout le projet et pas seulement de l'algorithme et du jeu. C'est pour cela que nous avons choisi de présenter un résultat plus correct qu'optimal (par exemple nous n'avons pas utilisé de représentation en _bitboards_, comme l'ont fait nos prédécesseurs, de même qu'ils n'ont pas eu l'algorithme à gérer).

### Répartition des tâches du projet

Pour mener à bien notre projet, les différentes tâches ont été réparties au sein des membres du groupe. Deux équipes ont été créées :

- Volodia et Romain Hubert pour la création du moteur du jeu en `C++` et optimisation du code (multithreading)
- Maxime, Romain Hu et Clément pour la création de l'interface Web et préparation du lien entre le moteur et la partie graphique

Finalement, la partie qui consistait à permettre de transporter le jeu codé en `C++` vers le navigateur a été faite par les membres des deux équipes (cf Bindings MCTS).

# Réalisation

## Notre environnement de développement

Devant la variété d'OS utilisés au cours de cette année par les membres de notre équipe et le fait que nous allions développer un stack technique peu commun en `C++` nous avons décidé de "simplifier" notre développement en utilisant les dernières fonctionnalités de VSCode et en utilisant le développement dans un *container* Docker. Cela permet au projet d'être extrêmement portable et d'être fonctionnel chez n'importe quel développeur !

Et en bonus nous avons réalisé ce rapport en `Markdown` afin qu'il soit facilement visible sur notre _repository_.

## Représentation du jeu

Notre encadrant nous a indiqué au tout début du projet un guide de méthodologies complet sur les plateaux hexagonaux et leurs représentations en informatique [@patel_blobs_2019]. En se basant sur ce guide et sur la forme rectangulaire de notre plateau, nous avons choisi une représentation en mémoire avec un conteneur associatif sous forme de table de hachage : `std::unordered_map`{.cpp}, d'une part afin d'obtenir une complexité en temps en $O(1)$ moyen et pas de $O(log(n))$ moyen avec les classiques, soit avec un conteneur associatif basé sur des arbres équilibrés : `std::map`{.cpp}. La représentation de la grille hexagonale sous forme rectangulaire crée des parties non utilisées dans le tableau  [@patel_blobs_2019, voir la section _map storage_].

## Points sensibles

Utiliser un algorithme tel que le MCTS implique que la vitesse et l’efficacité de ce dernier vont grandement être impactés par la représentation. Pour le MCTS, deux méthodes de la représentation du jeu ont un impact très important pour le niveau de l'intelligence artificielle que l'on obtient :

- la méthode servant à donner tous les cas disponibles pour un joueur, qui doit en effet analyser quelles routes sont possibles et jusqu'à quel endroit[^movesavailable];
- la méthode servant à donner l'état du jeu (aussi utilisée pour connaître le joueur suivant [^nextplayer]) qui doit vérifier s'il est encore possible pour un joueur de bouger [^movesavailable].

Une passe d'optimisation a déjà été réalisée sur la deuxième méthode qui reposait à la base sur la première (dans un effort d'obtenir le plus vite une démo fonctionnelle afin de déboguer des points plus vitaux). Cependant le temps manque pour faire plus, notamment nos prédécesseurs ont eu le temps[^theyhadtime] de vraiment attaquer le vif de l'optimisation, notamment avec les _bitboards_, qui leur ont permis une belle différence de performance (sans compter ici le fait que nous développons pour le web).

[^movesavailable]: Un pingouin peut être bloqué par un trou dans le plateau ou un autre pingouin.
[^nextplayer]: Il arrive qu'un joueur soit bloqué et qu'attendre son tour ne serve à rien, son adversaire peut lui continuer à récolter tous les points.
[^theyhadtime]: L'équipe précédente n'a pas eu à faire le MCTS et avait directement une interface connectant la représentation avec cet algorithme, sur laquelle nous avons dû faire quelques ajustements après avoir développé la représentation du jeu des pingouins. Nous faisons allusion ici à une différence entre le pion et le joueur : un joueur peut posséder plusieurs pions et ceci n'était pas une contrainte sur notre première phase de tests avec un morpion...

## MCTS

Le *Monte Carlo Tree Search* (ou MCTS) est un algorithme de recherche heuristique. C'est un algorithme qui explore l'arbre des possibles. Au fur et à mesure que l'algorithme se déroule, cet arbre grandit. Il essaye d'explorer toutes les parties possibles du jeu, en privilégiant les issues favorables pour lui. L'arbre est composé de noeuds répartis sur plusieurs couches. Chaque noeud représente une configuration, et ses enfants sont les configurations suivantes. Les noeuds doivent aussi stocker le nombre de parties gagnantes et le nombre total de simulations (à partir de ce noeud).

!["test légende"](yaktocat.png)

Le principe de l'algorithme est simple ; il n'y a que quatre étapes. On commence par choisir le "meilleur" noeud terminal. On détermine le meilleur noeud terminal grâce à la fonction UCT qui permet d'évaluer le meilleur compromis entre le nombre de visites et le résultat du noeud. Puis on crée ses enfants. Ensuite, on choisit un de ses enfants et on simule une partie aléatoire. Enfin, on transmet ce résultat sur tous les noeuds jusqu'à la racine.

On répète ces 4 étapes jusqu'à ce qu'on arrête l'algorithme. Ensuite, il nous retourne le meilleur coup à jouer, basé sur le nombre de visites des enfants de la racine.

## Multithreading

Afin d'augmenter les performances du MCTS, nous nous sommes penchés sur le multithreading. En effet, cela nous débloque la possibilité de simuler plusieurs parties en même temps, impliquant une augmentation du nombre de parties simulées. Il y a différentes manières de multithreader le MCTS; la _tree parallelization_, la _root parallelization_ et la _leaf parallelization_. D'après cette étude [@mass_par_mcts; @par_mcts], la _root parallelization_ semble la meilleure puisqu'elle permet d'explorer plus d'issues que les autres méthodes. Ainsi, cela augmente les chances de victoire du MCTS. De plus, cette méthode est facile à implémenter. En effet, il suffit d'assigner un arbre sur chaque thread. Les arbres sont donc développés indépendamment entre eux, donc il y a moins de chances que l'algorithme se bloque sur un minimum local. A la fin du temps alloué, nous mettons en commun les arbres, uniquement la première couche pour diminuer le temps de calcul. Ensuite, nous choisissons le meilleur coup à jouer.

Pour éviter de recréer l'arbre à chaque fois, nous avons mis en place un système de déplacement de la racine à un de ses enfants, gardant ainsi le sous-arbre de l'enfant.

## Interface graphique

Pour offrir une expérience de jeu optimale, et afin d'exporter le jeu sur un navigateur, nous avons dû mettre en place une interface graphique pour notre jeu. Avec les contraintes de temps et les contraintes techniques, nous avons été amenés à faire des choix aux niveaux des technologies utilisées et des méthodes d'implémentation afin de pouvoir produire rapidement une interface utilisable.

### Angular / Ionic

Afin de mettre en place, un code solide et rapidement exploitable, nous voulions impérativement utiliser `Typescript`, pour réaliser le moteur de jeu côté graphisme. En effet, son contrôle de typage est un véritable plus, par rapport à notre preuve de concept, où le moteur du Tic-Tac-Toe était en `Javascript`.
D'autre part, nous voulions construire une architecture de site Web plus globale qui viendrait englober la partie véritablement jouable. Afin de mettre en place cette architecture web sur pied au plus vite, nous nous avons décidé d'utiliser `Angular`.

Pour mettre en place la charte graphique de notre application, nous nous sommes tournés vers le framework `Ionic 4`, sorti récemment, qui offre aux développeurs des thèmes pré-conçus et des composants adaptatifs. Basé sur `Angular`, il s'intègre donc parfaitement dans notre projet.

### Organisation de l'application

Dans sa version finale notre application se compose des pages principales suivantes :

- une page d'accueil présentant le projet,
- une page avec le jeu en lui même,
- une page de présentation pour les membres de l'équipe,
- et une page pour les crédits.

Cette dernière permet de présenter le projet dans sa globalité, ainsi que les membres de l'équipe ayant participé à sa réalisation.

En utilisant `ngx rocket`, la base de l'application a pu être générée rapidement et avec une qualité de production. De cette manière notre application a pu disposer d'un service de routage et d'un autre de traduction que nous avons agrémenté au fur et à mesure des différents ajouts de pages et de fonctionnalités.

Durant nos recherches dans les différentes possibilités que pouvaient nous offrir _Ionic_, nous avons mis en place la possibilité d'accéder à une deuxième charte graphique, définissant le `Dark Theme`.

### Développement du jeu

## _Bindings_ MCTS

Il existe deux façons de faire des _bindings_ sur `Emscripten`. La première consiste à indiquer tous les noms des fonctions à exporter. Nous l'avons testé lors de notre preuve de concept sur le morpion. Nous avons retenu la seconde : _Embind_[@embind]. Cette dernière permet de réaliser des _bindings_ plus proprement sur des classes entières et leur ascendance. Nous avons mis en place une organisation un peu à la `Angular` : une fichier par dossier qui joue le rôle d'un module et qui contient tous les exports des classes locales. Ceci permet également de garder une compatibilité parfaite entre les deux plateformes sur lesquels nous développons : le Web et l'environnement Linux natif. _Embind_ permet également l'export des pointeurs[^whatpointers], ce qui est tout à notre bénéfice pour éviter d'avoir à ajouter des méthodes juste pour `Emscripten`.

Un second défi aura été de lier le programme une fois multithreadé avec `pthreads`[@pthreads_emscripten]. En effet, le Web a introduit des _threads_ particuliers : les _WebWorkers_. Cependant ils possèdent leur propre espace mémoire complètement séparé de l'application et ne permettent qu'une communication via `int` ou `strings`. Heureusement pour nous le plus gros du travail est réalisé par `Emscripten` mais nous avons néanmoins eu un problème inacceptable : le blocage du _thread_ principal de notre application (à cause de la méthode d'attente de résolution des threads). Pour pallier cela nous avons mis en place un mécanisme reposant sur _Asyncify_ [@asyncify] qui permet des `pause` et `resume` dans le code `C++` et donc la poursuite des évènements asynchrones tant appréciés de `JS`. La solution ne s'arrête pas là puisque nous avons dû utiliser un mécanisme d'attente des _threads_ non-bloquants en utilisant une boucle infinie accompagné d'un temporisateur, permettant ainsi de faire reprendre la main à l'application `Angular` pendant quelques millisecondes. Mais ce n'est pas fini, en effet, il faut également pouvoir retourner une valeur, ce que _Asyncify_ ne permet apparemment pas, la subtilité ici a été d'écrire une fonction `JavaScript` directement dans le code source `C++` afin de notifier l'application qu'une nouvelle valeur était prête à être lue.

[^whatpointers]: Il existe les pointeurs intelligents en C++, seulement notre première utilisation de ces derniers a été d'utiliser la version `std::shared_pointers`{.cpp} à la première occasion. Devant notre ignorance nous nous sommes rabattus sur le classique des pointeurs `C`. Si nous avions continué nous aurions certainement abusé des pointeurs `shared` et fini par perdre massivement en performance et en mémoire, surtout que nous avions déjà en tête de multithreader notre application. Nous ne parlons que des `shared_pointers` puisque nous ne connaissions pas réellement les mécanismes de _ownership_ des `unique_pointers`.

# Conclusion

conclusion
