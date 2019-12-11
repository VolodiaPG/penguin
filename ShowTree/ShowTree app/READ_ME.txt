2 méthodes de lancements sont possibles:
	1: double cliquer sur le jar
	2: executer par l'invite de commande:
		./ShowTree.jar <fichier source>

Le format du fichier d'import:

n°pos;n°de position;n°de victoires;n°de visites

ex:

0;-1;36;36 //
1;0;13;6
...

A noter que les 3 dernières colonnes peuvent ne pas respecter le format,
ce sont des Strings qui vont être afficher, il n'y a pas de traitement sur ceux ci.

Seul la première colonne importe vu que ça defini l'arbre.
A noter que la racine porte toujours le numero 0 au début.
1 correspond aux fils de la racine.
2 tout dépend du positionnement dans le log:
racine:	0;;;
noeud1:	1;;;
noeud2:	2;;;
noeud3:	1;;;
n'aura pas le même effet que:
racine:	0;;;
noeud1:	1;;;
noeud2:	1;;;
noeud3: 2;;;

Dans le 1er cas, noeud1 et noeud3 seront freres et le noeud2 sera le fils du noeud 1.
Alors que dans le 2e cas, noeud1 et noeud2 seront frêres er noeud3 sera le fils de noeud2

