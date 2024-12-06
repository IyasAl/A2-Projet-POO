#include "../include/GameOfLife.h" // Inclusion de l'en-tête GameOFLife.h
#include "../include/Button.h" // Inclusion de l'en-tête Button.h
#include <iostream> //  pour les entrées/sorties standard
#include <string> // Inclusion pour manipuler les chaînes de caractères
#include <limits> // pour obtenir les limites des types
#include <limits> // pour obtenir les limites des types
#include <cctype> // Pour utiliser std::isdigit

// Fonction pour vérifier si un fichier est au format .txt
bool isTxtFile(const std::string &filename) {
    // Vérifie si la taille de la chaîne est suffisante et si l'extension est ".txt"
    if (filename.size() >= 4 && filename.substr(filename.size() - 4) == ".txt") {
        return true;
    }
    return false;
}

// Fonction pour valider si une chaîne est un entier positif
bool isNumber(const std::string& str) {
    // Parcourt chaque caractère de la chaîne pour vérifier s'il est numérique
    for (char const &c : str) {
        if (!std::isdigit(c)) {  // Si un caractère n'est pas un chiffre
            return false; // Retourne faux
        }
    }
    return true; // Retourne vrai si tous les caractères sont des chiffres
}

// Fonction pour demander à l'utilisateur s'il souhaite inclure des obstacles
bool getValidatedInput(bool &value) {
    std::string input;
    while (true) {
        std::cout << "Inclure obstacles? (1: Oui, 0: Non): "; // choisir s'il veux inclure des obstacles ou non
        std::cin >> input;
         

        // Vérifie si l'utilisateur a entré une réponse valide
        if (input == "1") {
            value = true; // Obstacles inclus
            return true;
        } else if (input == "0") {
            value = false; // Obstacles non inclus
            return true;
        } else {
            std::cerr << "Entrée invalide. Veuillez saisir 1 pour Oui ou 0 pour Non." << std::endl; // Message d'erreur si l'entrée est invalide
        }
    }
}

// Fonction pour obtenir le mode choisi par l'utilisateur (console ou graphique)
int getValidatedMode() {
    std::string input;
    while (true) {
        std::cout << "Choisissez un mode:\n1. Console\n2. Graphical\n"; // Invite l'utilisateur à choisir un mode
        std::cin >> input;
        

        // Vérifie si le choix est valide
        if (input == "1" || input == "2") {
            return std::stoi(input); // Convertit le choix en entier
        } else {
            // Message d'erreur si l'entrée est invalide
            std::cerr << "Choix invalide. Veuillez saisir 1 pour le mode console ou 2 pour le mode graphique." << std::endl;
        }
    }
}

int main(int argc, char** argv) {
    if (argc < 3) { // Vérifie que le programme a été lancé avec au moins 3 arguments
        std::cerr << "format: " << argv[0] << " <filename> <max_iterations>" << std::endl;
        return 1; // Retourne une erreur si les arguments sont insuffisants
    }

    std::string filename = argv[1]; // Récupère le nom du fichier


    // Vérifie que le fichier est un fichier texte (.txt)
    if (!isTxtFile(filename)) {
        std::cerr << "Erreur : Le fichier doit être au format .txt !" << std::endl;
        return 1; // Retourne une erreur si le fichier n'est pas au bon format
    }

    std::string maxIterationsStr = argv[2]; // Récupère le nombre d'itérations sous forme de chaîne


    // Validation de maxIterations
    if (!isNumber(maxIterationsStr)) { // Vérifie que c'est un entier positif
        std::cerr << "Erreur : Le nombre d'itérations doit être un entier positif !" << std::endl;
        return 1;
    }

    int maxIterations = std::stoi(maxIterationsStr); // Convertit la chaîne en entier
    if (maxIterations <= 0) { // Vérifie que le nombre est strictement positif
        std::cerr << "Erreur : Le nombre d'itérations doit être strictement supérieur à zéro !" << std::endl;
        return 1;
    }

    // Demande à l'utilisateur s'il souhaite inclure des obstacles
    bool includeObstacles;
    getValidatedInput(includeObstacles);

    try {
        // Crée une instance du jeu en vérifiant le fichier d'entrée
        GameOfLife game(filename, maxIterations, includeObstacles, false);

        // Demande le mode choisi par l'utilisateur (console ou graphique)
        int choice = getValidatedMode();

        // Exécute le jeu en fonction du mode choisi
        if (choice == 1) {
            game.runConsoleMode(); // Mode console
        } else if (choice == 2) {
            game.runMenu(); // Mode graphique
        }
    } catch (const std::exception &e) {
        std::cerr << "Erreur : " << e.what() << std::endl; // Gère les exceptions et affiche un message d'erreur
        return 1; // Retourne une erreur
    }

    return 0; // Indique que le programme s'est terminé avec succès
}
