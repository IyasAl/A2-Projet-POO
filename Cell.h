#ifndef CELL_H    //si CELL_H n'est pas encore défini
#define CELL_H    //le définir maintenant

enum class CellState {  //définir une enum pour les différents états
    Dead,
    Alive,
    Obstacle
};

class Cell {
protected: 
    CellState state; //protected pour permettre aux classes dérivees d'accéder directemetn a state(heritage)
    CellState nextState; //protected pour permettre aux classes dérivees d'accéder directemetn a Nextstate 

public:
    Cell(CellState initialState = CellState::Dead); //Si aucun état n'est fourni lors de l'instanciation, il utilise la valeur par défaut CellState::Dead 
    virtual ~Cell();

    virtual CellState getState() const;
    virtual void setState(CellState newState);
    virtual void setNextState(CellState newNextState); // gère uniquement le calcul de l'état suivant
    virtual void updateState();    // applique ces changements (pour synchronisation des mises à jour)
    virtual bool isObstacle() const;
};

class AliveCell : public Cell {
public:
    AliveCell();
    void setNextState(CellState newNextState) override;
};

class DeadCell : public Cell {
public:
    DeadCell();
    void setNextState(CellState newNextState) override;
};

class ObstacleCell : public Cell {
public:
    ObstacleCell();
    void setState(CellState) override;
    void setNextState(CellState) override;
    void updateState() override;
    bool isObstacle() const override;
};

#endif // CELL_H
