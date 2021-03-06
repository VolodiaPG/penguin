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

"Pingouins" est un jeu de stratégie et de plateau sur lequel s'affrontent 2 à 4 joueurs. Le plateau contient 60 cases hexagonales qui comportent 1 à 3 poissons.

En début de partie, chaque joueur place un certain nombre de pingouins (de 2 à 4 suivant le nombre de joueurs) sur le plateau. A chaque tour, le joueur doit, si possible, bouger l'un de ses pingouins. Les déplacements autorisés se font en ligne droite suivant les 6 faces de la case hexagonale sur laquelle se trouve le pingouin. Il ne peut passer par-dessus des trous ou au-dessus d'autres pingouins, peu importe qu'ils appartiennent ou non au même joueur. Une fois le mouvement achevé, la case de départ est retirée du plateau. Le joueur peut alors incrémenter son score du nombre de poissons qu'il y avait sur cette case. 

Le jeu se termine lorsque plus aucun pingouin ne peut se déplacer. Le joueur avec le plus de points (poissons) remporte la partie.

# Sujet

Le sujet portait sur l'implémentation de ce jeu dans un environnement Web, en utilisant le nouveau standard _WebAssembly_. Les sources du projet sont compilées avec _Emscripten_ qui permet de coder en _C++_ pour la partie algorithmique. L'interface devait se faire avec les bibliothèques _Simple DirectMedia Layer_.

## Précédemment

Ce projet n'est pas nouveau. Une précédente équipe a déjà réalisé une application bureau, en _Java_. Cependant, notre cahier des charges était différent, notamment nous devions déployer le jeu sur le Web. Ainsi pour préparer ce passage sur le Web, et faciliter notre compréhension du MCTS, nous avons décidé de reprendre la logique du début. De plus le fait que _WebAssembly_soit aussi récent, certaines fonctionnalités, comme la parallélisation de l'algorithme, semblaient plus simple à réécrire qu'à adapter telles quelles.

## Preuve de Concept

Afin de tester la faisabilité et les différentes technologies, nous avons décidé de procéder à la création de l'algorithme de façon abstraite et de tester avec un jeu simple et facilement implémentable : le morpion (servant alors de _Preuve de Concept_ - PdC). Pour la partie graphique, nous avons simplement codé en JavaScript pur. Pour la suite du projet, et afin de faciliter le développement de la partie graphique, nous avons choisi de développer une application _Angular_. Sur la PdC, nous avions testé une technologie complémentaire pour gérer le graphisme du jeu : _PixiJS_. Cependant, l'expérience n'a pas été fructueuse. En effet, _PixiJS_ nécessite une gestion asynchrone de son canvas, son intégration dans une application _Angular_ doit donc se faire dans une zone indépendante, le lien avec le _WebAssembly_ devenait alors trop complexe. 

## Répartition

Pour mener à bien notre projet, les différentes tâches ont été réparties au sein des membres du groupe. Deux équipes ont été créées :

- Volodia P.-G. et Romain Hubert pour la création du moteur du jeu en _C++_ et optimisation du code ;
- Maxime G., Romain Hu et Clément C. pour la création de l'interface Web et préparation du lien entre le moteur du jeu et la partie graphique.

Finalement,  la tâche qui consistait à permettre de transporter le jeu codé en _C++_ vers le navigateur a été faite par les membres des deux équipes.


# Réalisation [^realisation]

[^realisation]: Toutes nos sources sont disponibles [@repo_git]. Nous avons également une démonstration en ligne [@repo_demo].

## Environnement de développement

Devant la variété d'OS utilisés au cours de cette année par les membres de notre équipe et le fait que nous allions développer un _stack_ technique peu commun en _C++_, nous avons décidé de "simplifier" notre développement en utilisant les dernières fonctionnalités de VSCode – développement dans un *container* Docker. Cela permet au projet d'être extrêmement portable et d'être fonctionnel chez n'importe quel développeur !

Et en bonus nous avons réalisé ce rapport en _Markdown_ afin qu'il soit facilement visible sur notre _repository_ [@repo_git].

## Représentation du jeu

Il est important de noter que le jeu, impose un plateau rectangulaire de N x N cases hexagonales. C'est pourquoi, une première étape de la représentation a été d'appréhender cette représentation, notamment à l'aide d'un guide de méthodologies complet [@patel_blobs_2019]. A partir de ce guide et des règles du jeu, nous avons choisi une représentation en mémoire avec un conteneur associatif sous forme de table de hachage : `std::unordered_map`{.cpp}. Cela permet d'obtenir une complexité moyenne en temps de $O(1)$ et pas de $O(log(n))$ avec les représentations classiques, soit avec un conteneur associatif basé sur des arbres équilibrés : `std::map`{.cpp}. La représentation de la grille hexagonale sous forme rectangulaire crée des parties non utilisées dans le tableau  [@patel_blobs_2019, voir la section _map storage_].


## Points sensibles

Les performances du MCTS sont liées à son efficacité et à sa vitesse d'exécution, ces derniers sont grandement impactés par la représentation du jeu. Pour le MCTS, deux méthodes de représentation sont alors possibles :

- une basée sur l'énumération de tous les cas disponibles pour un joueur, et d'une analyse des mouvements possibles.[^movesavailable] ;
- l'autre basée sur l'état du jeu, afin de connaître à tout instant le joueur qui doit jouer [^nextplayer], et s'il est encore possible pour lui de bouger [^movesavailable].

Pour obtenir au plus vite une démonstration fonctionnelle pour le débogage, nous avons optimisé la deuxième représentation avec une énumération efficace des cas possibles. Cependant par manque de temps, contrairement à nos prédécesseurs [^theyhadtime], nous n'avons pas pu pousser l'optimisation aussi loin. En particulier avec la mise en place de _bitboards_, qui augmentent de manière significative les performances, qui nécessitent pas mal de temps pour le déployer sur le Web.

[^movesavailable]: Un pingouin peut être bloqué par un trou dans le plateau ou un autre pingouin.
[^nextplayer]: Il arrive qu'un joueur soit bloqué et qu'attendre son tour ne serve à rien, son adversaire peut lui continuer à récolter tous les points.
[^theyhadtime]: L'équipe précédente n'a pas eu à faire le MCTS et avait directement une interface connectant la représentation avec cet algorithme, sur laquelle nous avons dû faire quelques ajustements après avoir développé la représentation du jeu des pingouins. Nous faisons allusion ici à une différence entre le pion et le joueur : un joueur peut posséder plusieurs pions et ceci n'était pas une contrainte sur notre première phase de tests avec un morpion...

# MCTS
## Principe

Le *Monte Carlo Tree Search* (_MCTS_) est un algorithme de recherche heuristique, qui explore l'arbre des possibles. Au fur et à mesure que l'algorithme se déroule, cet arbre grandit. Son objectif est d'explorer toutes les parties possibles du jeu, en privilégiant les issues favorables. L'arbre est composé de nœuds, représentant une configuration particulière, les nœuds fils qui en découlent, proviennent d'un mouvement particulier. Les nœuds doivent aussi stocker le nombre de parties gagnées jusque là, ainsi que le nombre simulations effectuées à partir de cette configuration.

L'algorithme se compose de quatre étapes :

- _Selection_ du "meilleur" nœud terminal, à l'aide de l'heuristique définie grâce à la fonction UCT [^uctformula], qui évalue le meilleur compromis entre le nombre de visites et le résultat du nœud,
- _Expansion_ de l'arbre, en créant les nœuds fils à partir des mouvements possibles, 
- _Simulation_ d'une partie aléatoire à partir d'un de ses nœuds fils,
- _Back Propagation_ du résultat de cette partie sur tous les nœuds ancêtres jusqu'à la racine.

![Les quatre étapes du MCTS](mcts.png)

Ces 4 étapes sont répétées jusqu'à arrêt de l'algorithme, soit à cause d'une limite de temps, soit à cause d'une limite d'itération. Après l'arrêt de la recherche, il retourne le meilleur coup à jouer, correspondant au nœud fils qui a le plus grand nombre de visites.

[^uctformula]: $\frac{w}{n} + c\sqrt{\frac{\ln N}{n}}$

## Parallélisation

Les performances du MCTS sont donc liées au nombre de parties qu'il peut simuler dans les limites imparties. Une des optimisation possible est donc de simuler plusieurs parties en même temps, avec du _multithreading_. Il y a différentes manières de paralléliser le MCTS; la _tree parallelization_, la _root parallelization_ et la _leaf parallelization_. D'après cette étude [@mass_par_mcts; @par_mcts], la _root parallelization_ semble la meilleure, puisqu'elle permet d'explorer plus d'issues que les autres méthodes, augmentant les chances de victoire du MCTS. De plus, sa facilité d'implémentation permet d'assigner un arbre sur chaque thread. Ces derniers sont donc développés indépendamment entre eux, diminuant ainsi les chances de bloquer sur un minimum local. A la fin du temps alloué, les arbres sont mis en commun à partir de leurs racines, afin de diminuer le temps de calcul. A la fin de cette opération, il est possible de choisir le meilleur coup à jouer.

Pour éviter de recréer l'arbre à chaque fois, nous avons mis en place un système de déplacement de la racine à un de ses enfants, gardant ainsi le sous-arbre de l'enfant.

# Interface graphique

Pour offrir une expérience de jeu optimale, et afin d'exporter le jeu sur un navigateur, nous avons dû mettre en place une interface graphique pour notre jeu. Avec les contraintes de temps et les contraintes techniques, nous avons été amenés à faire des choix aux niveaux des technologies utilisées et des méthodes d'implémentation afin de pouvoir produire rapidement une interface utilisable.

## _Angular_ & _Ionic_

Afin de mettre en place, un code solide et rapidement exploitable, nous voulions impérativement utiliser _Typescript_, pour réaliser le moteur de jeu côté graphisme. En effet, son contrôle de typage est un véritable plus, par rapport à notre preuve de concept, où le moteur du morpion était en _Javascript_.
D'autre part, nous voulions construire une architecture de site Web plus globale qui viendrait englober la partie véritablement jouable. Afin de mettre en place cette architecture Web sur pied au plus vite, nous avons décidé d'utiliser _Angular_.

Pour mettre en place la charte graphique de notre application, nous nous sommes tournés vers le framework _Ionic 4_, sorti récemment, qui offre aux développeurs des thèmes pré-conçus et des composants adaptatifs. Basé sur _Angular_, il s'intègre donc parfaitement dans notre projet.

## Organisation de l'application

Dans sa version finale notre application se compose des pages principales suivantes :

- une page d'accueil présentant le projet ;
- une page avec le jeu en lui même ;
- une page de présentation pour les membres de l'équipe ;
- et une page pour les crédits.

![Aperçu interface graphique](penguinApp.png)

Cette dernière permet, en plus de mettre à disposition le jeu des pingouins dans un navigateur Web, de présenter le projet dans sa globalité, ainsi que les membres de l'équipe ayant participé à sa réalisation. L'ensemble du rendu graphique est défini par un ensemble de composants venant s'incruster dans des _pages_ _Ionic_. La gestion et la levée d'évènements se fait conformément au standard _Angular_, et par un jeu de double lien dans la hiérarchie des composants.

Durant nos recherches dans les différentes possibilités que pouvaient nous offrir _Ionic_, nous avons mis en place la possibilité d'accéder à une deuxième charte graphique, définissant le _Dark Theme_.


## Automates à états finis

Que ce soit pour l'application entière, ou le jeu en particulier il a fallu mettre en place des automates finis (_Finite-State Machine_), afin de gérer le flot de contrôle, et contenir les actions possibles en fonction de l'état d'avancement. 


Le flot de contrôle est modélisé par 2 machines à états : 

- une pour l'application globale (apparition des différents composants en fonction des interactions avec l'utilisateur) ;
- une deuxième pour gérer exclusivement le jeu.

Pour mettre en place ces automates finis, nous avons utilisé la librairie _Typescript_ `+xstate`, permettant de mettre en place rapidement des automates sous le format _JSON_. Cette dernière offre aussi un système de visualisation des machines.

![Aperçu Automate fini du jeu](gameMachine.png)

L'Automate du jeu permet de dérouler la logique du jeu des pingouins, en limitant les interactions en fonction du joueur qui doit jouer. Le passage d'un état à un autre se fait par le déclenchement d'une action pré-enregistrée, souvent cette dernière est associée à un événement sur un composant _Ionic_. La progression dans le jeu se fait donc complètement indépendamment de l'application dans laquelle il est intégré. 

Cette manipulation d'états et d'événements permet d'offrir à l'utilisateur une interaction agréable et visuelle avec le plateau de jeu.



# Liens entre toutes les parties

## Lien entre interface graphique, représentation et MCTS

Il faut maintenant faire le lien entre l'interface graphique et le cœur du jeu. Il existe plusieurs niveaux de difficulté pour réaliser ces liens. Le plus simple nous l'avons utilisé lors de notre preuve de concept avec le morpion. Il consiste à marquer les fonctions à exporter directement dans la commande de compilation et est adaptée pour une petite quantité de fonctions. Cependant, le passage à l'échelle ne se fait pas bien, c'est pour cela que nous avons utilisé la seconde méthode : _Embind_ [@embind].

Elle se traduit pour l'utilisateur en de simples lignes d'export de méthodes dans un préprocesseur. Les seules difficultés peuvent venir des _templates_ en _C++_ qui peuvent faire grossir le code, mais un préprocesseur adapté suffit à limiter cela et de l'organisation générale du projet. C'est-à-dire que suivant où l'on situe ces lignes de lien, on peut avoir du mal à savoir quels classes sont concernées, c'est pour cela qu'en nous inspirant de _Angular_ nous avons un fichier avec l'extension `*.bind.cpp` qui reprend toutes les fonctions exportées dans le dossier courant et permet ainsi d'avoir très peu de méthodes à écrire spécifiques aux les liens. Le compilateur se charge alors de réaliser ces liens automatiquement (et mêmes des pointeurs[^whatpointers] !). De plus la clarté gagnée par cette structure permet aussi de continuer à garder deux plateformes pour développer : le Web et Linux pour avoir accès à l'éventail d'outils de débogage existants.

## Parallélisation

Notre second défi a été de lier la version parallélisée de notre programme avec `pthreads`[@pthreads_emscripten] et l'interface graphique. En effet, le Web a introduit sa propre version des _threads_ : les _WebWorkers_[^onWebworkers]. Cependant ils possèdent leur propre espace mémoire complètement séparé de l'application et ne permettent qu'une communication via des types primitifs : les `int` ou les `strings`. Il n'est donc pas aisé de communiquer des valeurs d'instances entres ces _WebWorkers_. Heureusement pour nous, le plus gros du travail est réalisé par _Emscripten_. Néanmoins, nous avons eu un problème inacceptable : le blocage du _thread_ principal de notre application lors du développement des arbres du MCTS, l'interface ne répondait alors plus. Pour pallier cela nous avons mis en place un mécanisme reposant sur _Asyncify_ [@asyncify] qui permet de faire des `pause` et `resume` dans le code _C++_ exporté. Plus largement ce module permet de rendre le code asynchrone et donc de poursuivre le traitement des évènements tant appréciés de _JavaScript_ lors de l’exécution de notre algorithme qui n'est alors plus bloquant. Le résultat n'est pourtant pas ce que nous espérions, puisque la fonction exécutant le MCTS ne renvoie alors plus de valeur au final. Nous avons alors défini une fonction _JavaScript_ dans le code _C++_, de façon à ce que ce dernier puisse l'appeler. Cette fonction permet alors d'émettre un événement après que la fonction _C++_ ait terminé [^whyafterterm]. Cette notification permet alors à l'interface de savoir quand récupérer la valeur de sortie et de pallier le problème initial.

[^whyafterterm]: Cela garantit que le traitement de l’événement se produit après la sortie de la fonction qui crée cet événement.
[^onWebworkers]: Tout comme le _WebAssembly_ les _WebWorkers_ ont un support encore limité aux versions récentes des navigateurs, pour ceux ne l'ayant pas désactivé pour des raisons de sécurité.
[^whatpointers]: Il existe les pointeurs intelligents en C++, seulement notre première utilisation de ces derniers a été d'utiliser la version `std::shared_pointers`{.cpp} à la première occasion. Devant notre ignorance nous nous sommes rabattus sur le classique des pointeurs _C_. Si nous avions continué nous aurions certainement abusé des pointeurs `shared` et fini par perdre massivement en performance et en mémoire, surtout que nous avions déjà en tête de paralléliser notre application. Nous ne parlons que des `shared_pointers` puisque nous ne connaissions pas réellement les mécanismes de propriété des `unique_pointers`.

# Conclusion {.unnumbered}

La mise en place de ce projet a permis de mettre en évidence les difficultés liées à la gestion de ce type de travail, notamment au niveau de l'organisation et les échéances temporelles. Notablement, au début nous n'avions pas les mêmes quantités de travail pour l'équipe graphique que pour la première version du MCTS.

Les technologies utilisées étaient le second point important de ce projet, certaines étaient déjà connues – voire maîtrisées – par des membres du groupe, néanmoins la plupart se sont avérées être une totale découverte. Il fallait donc être capable d'acquérir des connaissances technologiques (_WebAssembly_, MCTS, _Multithreading_, _Angular_ ...) mais également dans les outils nécessaires pour travailler dans une position peu commune (_VSCode_, _Docker_, _Doxygen_, _Compodoc_)  tout en développant  – pour permettre au projet d'avancer. Finalement, le résultat attendu par le cahier des charges a été plus qu'atteint : en effet, nous sommes en mesure de proposer un jeu des pingouins, implémentant une intelligence artificielle, et jouable à partir d'un navigateur Web. Nous avons démontré la viabilité et la maturité du _WebAssembly_[^wasmmature], tout en se heurtant à des obstacles – pas impossibles à passer – mais néanmoins gênants pour un environnement de production. Cette expérience nous a permis, en plus d'approfondir nos connaissances acquises au cours de l'année, de mieux connaître le fonctionnement de chacun et d'apprendre, en demandant conseil à notre encadrant lorsque cela devenait ardu, mais aussi à présenter notre travail [^englishisnotmyfav].

Pour finir : 

> _Laissons l'avenir dire la vérité, et évaluer chacun en fonction de son travail et de ses accomplissements. Le présent est à eux ; le futur, pour lequel j'ai réellement travaillé, est mien._
>
> -- <cite>Nikola Tesla</cite>

[^wasmmature]: un point étonnant est la possibilité d'allier deux géants dans leurs domaines : la versatilité du _JavaScript_ et la puissance crue du _C++_.
[^englishisnotmyfav]: L’exercice s'est avéré étrange mais encourageant. 