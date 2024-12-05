#pragma once //Directive qui garantit que le fichier d’en-tête n'est inclus qu'une seule fois dans le processus de compilation
#include "Button.h" //Inclut le fichier d'en-tête Button.h
#include "Grid.h" //Inclut le fichier d'en-tête Grid.h
#include <string> //pour manipuler des chaînes de caractères (std::string)

class GameOfLife {
private:
    Grid grid; // Instance de la grille représentant l'état de l'automate cellulaire
    int maxIterations; // Nombre maximal d'itérations à exécuter dans la simulation

    bool ispause; // Indique si la simulation est actuellement en pause (utilisée en mode graphique).

public:
    // Constructeur : Initialise une instance du jeu avec une grille chargée depuis un fichier,
    // un nombre maximal d'itérations, une option pour inclure les obstacles, et un état de pause initial.
    GameOfLife(const std::string &filename, int maxIter, bool includeObstacles,  bool ispause);

    void runConsoleMode(); //fonction qui Lance la simulation en mode console.
    void runGraphicMode(int cellSize = 20); // Lance la simulation en mode graphique avec SFML et le paramètre `cellSize` contrôle la taille des cellules
    void saveToFile(int iteration, const std::string &outputDir) const;  // Sauvegarde l'état actuel de la grille dans un fichier texte pour une itération donnée avec numéro de l'itération à sauvegarder et le répertoire où le fichier sera enregistré.
    void pause_resume(); // Met la simulation en pause
    void runMenu(); // Affiche un menu graphique pour lancer ou quitter la simulation.
};
