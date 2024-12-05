#pragma once //Directive qui garantit que le fichier d’en-tête n'est inclus qu'une seule fois dans le processus de compilation
#include <vector> //pour utiliser la classe std::vector, qui est une structure de données dynamique
#include <string> //pour utiliser la classe std::string pour manipuler des chaînes de caractères
#include "Cell.h" //Inclut le fichier d'en-tête Cell.h
#include <SFML/Graphics.hpp> //Inclut la bibliothèque SFML pour les fonctionnalités graphiques, notamment pour dessiner la grille à l'écran

class Grid { 
private: //Déclare la section privée
    int rows, cols; //Nombre de lignes (rows) et de colonnes (cols) dans la grille
    std::vector<std::vector<Cell*>> cells; //Grille représentée comme un tableau dynamique de pointeurs vers des objets de type Cell
    std::string filename; // Nom du fichier associé à la grille (pour charger ou sauvegrader des données)

    int countAliveNeighbors(int x, int y) const; //Compte le nombre de voisins vivants autour de la cellule à la position (x, y).

public: //Déclare la section publique
    Grid(int r, int c, const std::string &filename = ""); //Constructeur pour initialiser une grille avec des dimensions et un fichier optionnel
    ~Grid(); //Destructeur pour libérer la mémoire utilisée par les cellules

    void loadFromFile(const std::string &filename, bool includeObstacles); //Charge une grille depuis un fichier, avec option pour inclure les obstacles.
    int getRows() const; //Renvoie le nombre de lignes 
    int getCols() const; //Renvoie le nombre de colonnes 
    std::string getFilename() const;  //Renvoie le nom du fichier associé à la grille
    Cell* getCell(int x, int y) const; //Renvoie un pointeur vers la cellule située à (x, y)

    void computeNextState(); //Calcule l'état suivant pour toutes les cellules de la grille
    void updateGrid(); //Applique les états calculés et met à jour toutes les cellules
    void printToConsole() const; //Affiche la grille actuelle dans la console (mode Console)
    void draw(sf::RenderWindow &window, int cellSize) const; // Dessine la grille dans une fenêtre graphique SFML avec des cellules de taille donnée.
};
