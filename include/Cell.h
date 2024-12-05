#pragma once //Directive qui garantit que le fichier d’en-tête n'est inclus qu'une seule fois dans le processus de compilation

enum class CellState {  // Enumération représentant l'état des cellules.
    Dead, // Cellule morte : n'interagit pas avec les autres cellules
    Alive, // Cellule vivante : interagit avec ses voisines selon les règles du jeu.
    Obstacle // Cellule obstacle : bloque l'interaction et ne peut pas changer d'état.
};

class Cell { //Classe Mere pour représenter une cellule générique.
protected: //Permet aux classes dérivées d'accéder directement à ces membres, tout en les cachant du reste du programme(préserver l'encapsulation)
    CellState state; //État actuel de la cellule (Dead, Alive ou Obstacle)
    CellState nextState; //État calculé pour le tour suivant, mais pas encore appliqué

public: //section Public
    Cell(CellState initialState = CellState::Dead); // Constructeur : initialise une cellule avec un état par défaut (Dead).
    virtual ~Cell(); //// Destructeur virtuel : permet un nettoyage correct lorsqu'on manipule des classes dérivées via un pointeur de base

    virtual CellState getState() const; // Renvoie l'état actuel de la cellule.
    virtual void setState(CellState newState); // Définit un nouvel état pour la cellule.
    virtual void setNextState(CellState newNextState); // Stocke l'état calculé pour le prochain tour.
    virtual void updateState(); // Applique l'état suivant comme état actuel
    virtual bool isObstacle() const; // Indique si la cellule est un obstacle
};

class AliveCell : public Cell { // Classe fille pour représenter une cellule vivante.
public:
    AliveCell(); // Constructeur : initialise une cellule avec l'état Alive
    void setNextState(CellState newNextState) override; // Implémente le comportement spécifique pour calculer le prochain état d'une cellule vivante
};

class DeadCell : public Cell { // Classe fille pour représenter une cellule morte.
public:
    DeadCell(); // Constructeur : initialise une cellule avec l'état Dead.
    void setNextState(CellState newNextState) override; // Implémente le comportement spécifique pour calculer le prochain état d'une cellule morte
};

class ObstacleCell : public Cell { // Classe fille  pour représenter une cellule obstacle.
public:
    ObstacleCell(); // Constructeur : initialise une cellule avec l'état Obstacle
    void setState(CellState) override; // maintient le comportement spécifique des cellules obstacles
    void setNextState(CellState) override; // Préserve la cohérence des cellules obstacles en bloquant toute transition vers un état futur.
    void updateState() override; //Garantit que l'état des cellules obstacles reste constant à chaque itération
    bool isObstacle() const override; //Retourne toujours true, indiquant que cette cellule est un obstacle.


};