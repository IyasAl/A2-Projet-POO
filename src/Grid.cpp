#include "../include/Grid.h" // Inclusion de l'en-tête Grid.h
#include <iostream> //  pour les entrées/sorties standard
#include <fstream> //  pour manipuler les fichiers
#include <stdexcept> //pour gérer les exceptions

// Constructeur de la classe Grid

Grid::Grid(int r, int c, const std::string &filename) : rows(r), cols(c), filename(filename), cells(r, std::vector<Cell*>(c, nullptr)) {}
// Destructeur de la classe Grid
Grid::~Grid() {
    for (auto &row : cells) {  // Parcourt chaque ligne de la grille
        for (auto &cell : row) { // Parcourt chaque cellule dans la ligne
            delete cell; // Libère la mémoire allouée dynamiquement pour chaque cellule

        }
    }
}




// Fonction pour charger une grille depuis un fichier
void Grid::loadFromFile(const std::string &filename, bool includeObstacles) { // Ouvre le fichier pour lecture
    std::ifstream file(filename); // Ouvre le fichier pour lecture
    if (!file) {// Vérifie si le fichier est ouvert avec succès
        throw std::runtime_error("Erreur : Impossible d'ouvrir le fichier !");
    }

    file >> rows >> cols; // Lit les dimensions de la grille
    if (file.fail()) {// Vérifie si les dimensions sont valides
        throw std::runtime_error("Erreur : Fichier invalide. Les dimensions doivent être des entiers.");
    }
    // Réinitialise la grille avec les nouvelles dimensions
    cells = std::vector<std::vector<Cell*>>(rows, std::vector<Cell*>(cols, nullptr));


    // Lecture des états des cellules depuis le fichier
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int state;
            file >> state; // Lit l'état de la cellule

            // Vérifie si l'état lu est valide 
            if (file.fail() || (state != 0 && state != 1 && state != 2)) {
                throw std::runtime_error(" Le fichier contient des valeurs invalides. "
                                         "Seules les valeurs 0, 1, et 2 sont acceptées !");
            }
            


            // Crée la cellule appropriée en fonction de son état
            if (state == 2 && includeObstacles) {
                cells[i][j] = new ObstacleCell();
            } else if (state == 1) {
                cells[i][j] = new AliveCell();
            } else {
                cells[i][j] = new DeadCell();
            }
        }
    }
}


// Retourne le nombre de lignes
int Grid::getRows() const {
    return rows;
}


// Retourne le nombre de colonnes
int Grid::getCols() const {
    return cols;
}


// Retourne le nom du fichier
std::string Grid::getFilename() const {
    return filename;
}


// Retourne une cellule spécifique
Cell* Grid::getCell(int x, int y) const {
    return cells[x][y];
}


// Calcule le prochain état de la grille
void Grid::computeNextState() {  //calcule le prochain etat de chaque cellule
    for (int x = 0; x < rows; ++x) { // Parcourt chaque ligne
        for (int y = 0; y < cols; ++y) { // Parcourt chaque cellule
            if (cells[x][y]->isObstacle()) continue; //ignorer les cellules obstacles et continue
            int aliveNeighbors = countAliveNeighbors(x, y);  // Compte les voisins vivants

            // Gestion des règles pour une cellule vivante
            if (cells[x][y]->getState() == CellState::Alive) {//Vérifie si la cellule est actuellement vivante.
                if (aliveNeighbors < 2 || aliveNeighbors > 3) { //La cellule meurt par sous-population(<2) ou surpopulation(>3)
                    cells[x][y]->setNextState(CellState::Dead);
                } else {
                    cells[x][y]->setNextState(CellState::Alive); //sinon elle reste vivante
                }
            } else if (cells[x][y]->getState() == CellState::Dead) { //si cellule est morte
                if (aliveNeighbors == 3) { //Une cellule morte devient vivante si elle a exactement 3 voisins vivants
                    cells[x][y]->setNextState(CellState::Alive);
                } else {
                    cells[x][y]->setNextState(CellState::Dead); //sinon elle reste morte
                }
            }
        }
    }
}


void Grid::updateGrid() {
    for (auto &row : cells) {          // Parcourt chaque ligne
        for (auto &cell : row) {       // Parcourt chaque cellule dans la ligne
            cell->updateState();       // Met à jour l'état de la cellule
        }
    }
}




void Grid::printToConsole() const {
    for (int i = 0; i < rows; ++i) {       // Parcourt les lignes
        for (int j = 0; j < cols; ++j) {   // Parcourt les colonnes
            if (cells[i][j]->getState() == CellState::Alive) {
                std::cout << "1 "; // Affiche 1 pour une cellule vivante
            } else if (cells[i][j]->getState() == CellState::Obstacle) {
                std::cout << "2 "; // Affiche 2 pour une cellule obstacle
            } else {
                std::cout << "0 "; // Affiche 0 pour une cellule morte
            }
        }
        std::cout << std::endl; // Fin de ligne après chaque rangée
    }
    std::cout << std::endl;     // Ligne vide pour espacement
}



// Compte les voisins vivants d'une cellule en considérant une grille torique
int Grid::countAliveNeighbors(int x, int y) const { 
    int aliveCount = 0;  // Initialise le compteur
    for (int i = -1; i <= 1; ++i) { // Parcourt les lignes autour de la cellule
        for (int j = -1; j <= 1; ++j) { // Parcourt les colonnes autour de la cellule
            if (i == 0 && j == 0) continue; // Ignore la cellule elle-même
            int nx = (x + i + rows) % rows; // Calcule la ligne voisine en mode torique
            int ny = (y + j + cols) % cols;  // Calcule la colonne voisine en mode torique
            if (cells[nx][ny]->getState() == CellState::Alive) { // Incrémente si le voisin est vivant
                ++aliveCount;
            }
        }
    }
    return aliveCount;
}


// Dessine la grille dans une fenêtre SFML
void Grid::draw(sf::RenderWindow &window, int cellSize) const {
    sf::RectangleShape cellShape(sf::Vector2f(cellSize - 1, cellSize - 1)); // Crée un rectangle pour chaque cellule
    for (int x = 0; x < rows; ++x) { // Parcourt les lignes
        for (int y = 0; y < cols; ++y) { // Parcourt les colonnes
            cellShape.setPosition(y * cellSize, x * cellSize); // Positionne le rectangle
            if (cells[x][y]->getState() == CellState::Alive) {
                cellShape.setFillColor(sf::Color::White); // Couleur blanche pour une cellule vivante
            } else if (cells[x][y]->getState() == CellState::Obstacle) {
                cellShape.setFillColor(sf::Color(105,105,105)); // Gris pour une cellule obstacle
            } else {
                cellShape.setFillColor(sf::Color::Black); // Noir pour une cellule morte
            }
            window.draw(cellShape); // Dessine la cellule dans la fenêtre
        }
    }
}
