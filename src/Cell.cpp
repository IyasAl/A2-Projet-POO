#include "../include/Cell.h" //Inclut le fichier d'en-tête "Cell.h"

Cell::Cell(CellState initialState) : state(initialState), nextState(CellState::Dead) {}// Constructeur de la classe Cell : Initialise une cellule avec un état initial (par défaut Dead) 
// et définit son prochain état à Dead.
Cell::~Cell() {} // Destructeur de la classe Cell : Nettoie la mémoire si nécessaire (vide ici car pas de ressources dynamiques).

CellState Cell::getState() const { // Renvoie l'état actuel de la cellule.
    return state; 
}

void Cell::setState(CellState newState) { // Définit l'état actuel de la cellule.
    state = newState;
}

void Cell::setNextState(CellState newNextState) { // Stocke le prochain état calculé de la cellule.
    nextState = newNextState;
}

void Cell::updateState() { // Met à jour l'état actuel de la cellule avec le prochain état calculé
    state = nextState;
}

bool Cell::isObstacle() const { // Indique que la cellule de base n'est pas un obstacle (surcharge dans les sous-classes si nécessaire).
    return false;
}

AliveCell::AliveCell() : Cell(CellState::Alive) {} // Constructeur de la classe dérivée AliveCell : Initialise une cellule vivante.

void AliveCell::setNextState(CellState newNextState) { // Définit le prochain état d'une cellule vivante.
    nextState = newNextState;
}

DeadCell::DeadCell() : Cell(CellState::Dead) {} // Constructeur de la classe dérivée DeadCell : Initialise une cellule morte.

void DeadCell::setNextState(CellState newNextState) { // Définit le prochain état d'une cellule morte.
    nextState = newNextState;
}

ObstacleCell::ObstacleCell() : Cell(CellState::Obstacle) {} // Constructeur de la classe dérivée ObstacleCell : Initialise une cellule obstacle.

void ObstacleCell::setState(CellState) {} // Redéfinition : L'état d'une cellule obstacle ne peut pas être modifié.

void ObstacleCell::setNextState(CellState) {} // Redéfinition : Le prochain état d'une cellule obstacle ne peut pas être défini.

void ObstacleCell::updateState() {} // Redéfinition : L'état d'une cellule obstacle reste toujours constant.

bool ObstacleCell::isObstacle() const { // Indique qu'une cellule obstacle est effectivement un obstacle.
    return true;
}
