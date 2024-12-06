#include "../include/GameOfLife.h" // Inclut le fichier d'en-tête GameOfLife.h
#include "../include/Button.h" // Inclut le fichier d'en-tête Button.h
#include <iostream> // Inclut la bibliothèque standard pour l'entrée/sortie.
#include <fstream> // Permet la gestion des fichiers pour sauvegarder les états.
#include <filesystem> // Fournit des fonctions pour créer et gérer des répertoires.
#include <thread>// Permet l'utilisation de threads et la temporisation des boucles.
#include <chrono>// Fournit des utilitaires pour gérer le temps.
#include <ctime>// Utilisé pour manipuler l'heure et la date.
#include <sstream>// Utilisé pour manipuler des chaînes de caractères comme des flux.



// Initialise un objet de simulation en créant une grille et en la chargeant depuis un fichier.
    // `grid(0, 0, filename)` initialise la grille avec 0 lignes et colonnes et associe un fichier de configuration.
    // `maxIterations` définit le nombre maximal d'itérations de la simulation.
    // `ispause` initialise l'état de pause à `false` (simulation active par défaut).

GameOfLife::GameOfLife(const std::string &filename, int maxIter, bool includeObstacles, bool ispause)
    : grid(0, 0, filename), maxIterations(maxIter), ispause(false) {
    grid.loadFromFile(filename, includeObstacles);  // Charge la grille depuis le fichier spécifié, avec l'option d'inclure ou non des obstacles

    
}


// Fonction qui sauvegarde l'état actuel de la grille dans un fichier texte.
    // Chaque fichier est nommé `iteration_<numéro>.txt` et placé dans un répertoire dédié.

void GameOfLife::saveToFile(int iteration, const std::string &outputDir) const {       
    std::ofstream outFile(outputDir + "/iteration_" + std::to_string(iteration) + ".txt");   // Crée et ouvre un fichier de sortie dans le répertoire `outputDir`, nommé avec le numéro de l'itération.   
    if (!outFile) { // Vérifie si le fichier n'a pas pu être créé ou ouvert.
        throw std::runtime_error("ne peut pas ouvrir le output du fichier"); // Lève une exception pour signaler l'erreur
    }

    // Tableau statique basé sur l'ordre des CellState
    const char stateMap[] = {'0', '1', '2'}; // Dead = 0, Alive = 1, Obstacle = 2

    for (int i = 0; i < grid.getRows(); ++i) { // Parcourt toutes les lignes de la grille.
        for (int j = 0; j < grid.getCols(); ++j) { // Parcourt toutes les colonnes de la ligne en cours.
            outFile << stateMap[static_cast<int>(grid.getCell(i, j)->getState())] << " "; // Écrit dans le fichier l'état actuel de la cellule à la position (i, j),
            //et converti en sa représentation textuelle grâce à `stateMap`.
        }
        outFile << "\n";  // Ajoute une nouvelle ligne après avoir parcouru toutes les colonnes d'une rangée.
    }
}

void GameOfLife::runConsoleMode() { // Fonction qui exécute la simulation en mode console, affichant l'évolution de la grille dans le terminal.
    
    std::time_t now = std::time(nullptr); // Obtient l'heure actuelle comme un timestamp.

    
    std::ostringstream oss; 
    oss << "output_" << grid.getFilename() << "_" // Génère un nom unique pour le répertoire de sortie, basé sur le nom du fichier de la grille
        << std::put_time(std::localtime(&now), "%Y%m%d_%H%M%S"); // et l'horodatage courant (format `YYYYMMDD_HHMMSS`).
    std::string outputDir = oss.str(); // Stocke le nom du répertoire généré

    
    std::filesystem::create_directory(outputDir); // Crée physiquement le répertoire de sortie pour stocker les fichiers d'état

    // Boucle principale de simulation
    for (int iteration = 0; iteration < maxIterations; ++iteration) {  // Boucle principale de simulation, itère pour chaque étape jusqu'au maximum défini.
        grid.printToConsole();              // Afficher la grille dans la console
        saveToFile(iteration, outputDir);   // Sauvegarder l'état actuel dans un fichier
        grid.computeNextState();            // Calculer l'état suivant
        grid.updateGrid();                  // Appliquer les mises à jour
    }
}


void GameOfLife::runGraphicMode(int cellSize) {  // Fonction qui exécute la simulation en mode graphique avec des cellules de taille spécifiée.
    int intervalle = 1000; // Définit l'intervalle entre deux étapes de simulation (en millisecondes).
    sf::RenderWindow window(sf::VideoMode(1280,720), "Game of Life");  // Crée une fenêtre graphique SFML avec une taille de 1280x720 pixels et un titre "Game of Life".


    sf::Font font2;  //Déclare un objet `font2` de type `sf::Font` (provenant de SFML).
    // Cet objet sera utilisé pour charger une police de caractères à partir d'un fichier.

    if (!font2.loadFromFile("./asset/font/league-spartan.bold.ttf")) { 
        // Charge une police à partir d'un fichier. Si cela échoue, affiche un message d'erreur et quitte la fonction.
        std::cerr << "Error loading font\n";
        return;
    }


    // Crée trois boutons :
    // - "Pause" pour suspendre ou reprendre la simulation.
    // - "+" pour accélérer la simulation.
    // - "-" pour ralentir la simulation.
    // - "quit" pour quitter.
    Button pauseButton(10, 650, 200, 50, "Pause", font2);
    Button plusButton(220, 650, 100, 50, "+",  font2);
    Button moinsButton(340, 650, 100, 50, "-", font2);
    Button quitButton(460, 650, 200, 50, "Quit", font2); 

    while (window.isOpen()) { // Boucle principale qui continue tant que la fenêtre est ouverte.
        sf::Event event;
        while (window.pollEvent(event)) { // Gère tous les événements utilisateurs (clics, fermetures, etc.) survenus depuis le dernier cycle.

            if (event.type == sf::Event::Closed) {
                window.close();} // Ferme la fenêtre si l'utilisateur clique sur le bouton de fermeture.

            if (pauseButton.isPressed(sf::Mouse::getPosition(window), event)) {
                pause_resume();  // Active ou désactive l'état de pause si le bouton "Pause" est cliqué.
            }

            if (plusButton.isPressed(sf::Mouse::getPosition(window), event)) {
                intervalle-=50; // Réduit l'intervalle de temporisation, ce qui accélère la simulation
            }

            if (moinsButton.isPressed(sf::Mouse::getPosition(window), event)) {
                intervalle+=50; // Augmente l'intervalle de temporisation, ce qui ralentit la simulation.
            }

             if (quitButton.isPressed(sf::Mouse::getPosition(window), event)) {
                window.close(); // Ferme la fenêtre si le bouton "Quit" est cliqué
            }
            
        }

        window.clear(sf::Color::Black); // Efface la fenêtre en la remplissant avec une couleur noire.

        if (!ispause) {

            grid.computeNextState(); // Calcule l'état suivant si la simulation n'est pas en pause.
            grid.updateGrid(); // Applique les changements calculés.

        }
        grid.draw(window, cellSize); // Dessine la grille dans la fenêtre avec la taille de cellules spécifiée.

        // Affiche les boutons dans la fenêtre.
        pauseButton.render(window); 
        plusButton.render(window);
        moinsButton.render(window);
        quitButton.render(window);
        window.display(); // Actualise la fenêtre pour refléter les changements graphiques.

        std::this_thread::sleep_for(std::chrono::milliseconds(intervalle)); // Attend l'intervalle défini avant de continuer à la prochaine étape
    }
}


void GameOfLife::pause_resume() {
    ispause = !ispause; // Si `ispause` vaut `true` (simulation en pause), elle devient `false` (simulation active), et vice-versa.
}

void GameOfLife::runMenu() {// Affiche un menu graphique permettant à l'utilisateur de lancer la simulation ou de quitter l'application.
     
    sf::RenderWindow menuWindow(sf::VideoMode(1280, 720), "Game of Life - Menu");  // Crée une fenêtre graphique avec une taille de 1280x720 pixels et un titre "Game of Life - Menu".
    
    sf::Texture t;
    t.loadFromFile("./asset/image/Background.png");  // Charge une texture d'image depuis le fichier spécifié (utilisée comme arrière-plan du menu).
    sf::Sprite s(t); // Associe la texture chargée à un objet `sf::Sprite` pour pouvoir l'afficher dans la fenêtre

    sf::Font font1;
    if (!font1.loadFromFile("./asset/font/league-spartan.bold.ttf")) {
        std::cerr << "Error loading font\n";
        return;
        // Charge une police depuis un fichier. Si le chargement échoue, affiche un message d'erreur
        // dans la console et termine la fonction (le menu ne peut pas fonctionner sans police).
    }

    Button startButton(237, 350, 300, 100, "Start",font1); // Crée un bouton "Start" avec une position de (237, 350), une taille de 300x100 pixels,
    startButton.setOutlineColor(sf::Color::White); // Définit la couleur du contour du bouton "Start" en blanc.
    Button quitButton(237, 509, 300, 100, "Quit",font1); // Crée un bouton "Quit" avec une position de (237, 509), une taille de 300x100 pixels,
    quitButton.setOutlineColor(sf::Color::White); // Définit la couleur du contour du bouton "Quit" en blanc.

    while (menuWindow.isOpen()) { // Boucle principale du menu. Elle continue tant que la fenêtre du menu est ouverte.
        sf::Event event;
        while (menuWindow.pollEvent(event)) { // Vérifie tous les événements utilisateur (clics, fermetures, etc.) qui se sont produits depuis le dernier cycle
            if (event.type == sf::Event::Closed) {  // Ferme la fenêtre si l'utilisateur clique sur le bouton de fermeture.
                menuWindow.close();
                return;
            }

            if (startButton.isPressed(sf::Mouse::getPosition(menuWindow), event)) {
                menuWindow.close(); // Si le bouton "Start" est cliqué, ferme la fenêtre du menu...
                runGraphicMode(); //...et lance le mode graphique de la simulation.
            }

            if (quitButton.isPressed(sf::Mouse::getPosition(menuWindow), event)) { // Si le bouton "Quit" est cliqué, ferme la fenêtre et termine la fonction
                menuWindow.close();
                return;
            }
        }

        menuWindow.clear(sf::Color::Black); // Efface le contenu de la fenêtre du menu et la remplit avec une couleur noire.
        menuWindow.draw(s); // Dessine l'arrière-plan (sprite associé à la texture).

        startButton.render(menuWindow); // Affiche le bouton "Start" dans la fenêtre.
        quitButton.render(menuWindow); // Affiche le bouton "Quit" dans la fenêtre.
        menuWindow.display(); // Actualise l'affichage de la fenêtre pour refléter les changements graphiques (boutons, fond, etc.).
    }
}