# Game of Life

Un simulateur du jeu de la vie implémenter C++/SFML avec mode console et graphique.

   Le jeu de la vie désigne un automate cellulaire proposé par le mathématicien John Conway. Il décrit l’évolution d’une population de cellules sur un intervalle de temps discret. Les cellules placées dans une grille rectangulaire deux dimensionnelle sont caractérisées par deux états ; elles sont soit vivantes, soit mortes. A l’exclusion des bordures, le voisinage d’une cellule est formé par 8 autres cellules directement adjacentes. Pour passer de l’itération t à l’itération t+1, l’état des cellules dans la grille est actualisé selon les règles suivantes :

- Une cellule morte possédant exactement trois voisines vivantes devient vivante.
- Une cellule vivante possédant deux ou trois voisines vivantes reste vivante, sinon elle meurt.

## Fonctionnalités

L’utilisateur lance le programme et fournit le chemin du fichier contenant l’état initial des cellules en paramètre.
Le programme consomme le fichier avec le format précédemment décrit et génère l’ensemble des objets du programme (grille, cellules).
A chaque itération les cellules changent d’état selon les règles énoncées plus haut.
L’exécution se termine lorsque l’automate n’évolue plus ou après un nombre d’itération fixé arbitrairement.
Deux modes de fonctionnement seront implémentés :

- Le premier, en mode console, fournira les états des n premières itérations de votre jeu de la vie. A chaque itération le programme écrit l’état des cellules dans un fichier selon le format décrit précedemment. Ces résultats sont stockés dans des dossiers nommés <nom_du_fichier_dentree>_out et utilisés pour correction.
- Le second, en mode graphique, affiche la grille et l’état des cellules sur une interface graphique. Pour aboutir, vous disposez d’un exemple de code capable d’afficher une fenêtre graphique et une grille de cellules. Celui-ci devra être adapté en une version orientée objet. La simulation démarre au lancement du programme. La durée entre deux itérations est contrôlable.

## Extensions 

Ce jeu propose 2 extensions : 

- Gestion d’une grille torique. Les cellules placées aux extrémités de la grille sont adjacentes ; en d’autres termes les cellules en colonne 0 sont voisines des cellules en colonne N−1, avec N le nombre de colonnes. Le principe est similaire en ligne.
- Introduction de cellules obstacle. L’état des cellules obstacles n’évolue pas au cours de l’exécution. Ces dernières possèdent un état vivant ou mort. Modifiez votre code, sans altérer le fonctionnement de base.

## Lancement du jeu

   1. Lancez le fichier GameOfLife avec le fichier contenant l'état initial de la matrice de ccellule et le nombre d'ittération.
```bash
   ./GameOfLife input.txt nombre_itteration
```
   2. Choisissez si vous voulez inclure les obstacles (extension).
      - 1 : Oui
      - 0 : Non
        
   3. Choisissez le mode d'affichage.
      - 1 : Console
      - 2 : Graphique
        
### Mode console :

   Le mode console prend la grille initiale et génère la simulation du jeu de la vie pour le nombre d'ittération donné en argument.
Pour chaque ittération, la grille est affiché dans la console et un fichier txt est créer dans un dossier nommé "output_input.txt_DATE_HEURE". Chaque fichier est nommé "itterartion" avec le nombre de l'ittération. Le nombre va de 0 à n-1. 

### Mode Graphique :

   Le mode graphique affiche tout d'abord un menu de démarage avec le choix de "start" et "quit". 
Quand l'utilisateur clique sur "start", la simulation commence avec comme état initial la grille donnée en argument. L'utilisateur a ensuite l'option de mettre en pause le jeu avec le bouton "Pause", d'accélérer/ralentir la simulation avec les boutons "+" et "-". Finalement, pour quitter le jeu, vous pouvez cliquez sur "Quit" ou fermer la fenêtre du jeu. 
Ce mode ne produit pas de fichier "output" et tourne à l'infini. 
   
## Prérequis

- SFML 2.5+ (ou récent)
- C++17 ou récent
- Un compilateur qui supporte C++17

## Installation
1. Clonez le dépôt :
   ```bash
   git clone https://github.com/VotreNomUtilisateur/MonProjet.git
   ./game_of_life input.txt 100

