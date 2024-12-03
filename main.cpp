#include "GameOfLife.h"
#include <iostream>
#include <string>
#include <limits>

bool getValidatedInput(bool &value) {
    std::string input;
    while (true) {
        std::cout << "Inclure obstacles? (1: oui, 0: Non): ";
        std::cin >> input;

        if (input == "1") {
            value = true;
            return true;
        } else if (input == "0") {
            value = false;
            return true;
        } else {
            std::cerr << "Entrée invalide. Veuillez saisir 1 pour Oui ou 0 pour Non." << std::endl;
        }
    }
}

int getValidatedMode() {
    std::string input;
    while (true) {
        std::cout << "Choose mode:\n1. Console\n2. Graphical\n";
        std::cin >> input;

        if (input == "1" || input == "2") {
            return std::stoi(input);
        } else {
            std::cerr << "Choix invalide. Veuillez saisir 1 pour le mode console ou 2 pour le mode graphique." << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " <filename> <max_iterations>\n";
        return 1;
    }

    std::string filename = argv[1];
    int maxIterations = std::stoi(argv[2]);

    bool includeObstacles;
    getValidatedInput(includeObstacles);

    GameOfLife game(filename, maxIterations, includeObstacles, false);

    int choice = getValidatedMode();

    if (choice == 1) {
        game.runConsoleMode();
    } else if (choice == 2) {
        game.runGraphicMode();
    }

    return 0;
}
