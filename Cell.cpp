#include "Cell.h"

Cell::Cell(CellState initialState) : state(initialState), nextState(CellState::Dead) {}
Cell::~Cell() {}

CellState Cell::getState() const {
    return state;
}

void Cell::setState(CellState newState) {
    state = newState;
}

void Cell::setNextState(CellState newNextState) {
    nextState = newNextState;
}

void Cell::updateState() {
    state = nextState;
}

bool Cell::isObstacle() const {
    return false;
}

AliveCell::AliveCell() : Cell(CellState::Alive) {}

void AliveCell::setNextState(CellState newNextState) {
    nextState = newNextState;
}

DeadCell::DeadCell() : Cell(CellState::Dead) {}

void DeadCell::setNextState(CellState newNextState) {
    nextState = newNextState;
}

ObstacleCell::ObstacleCell() : Cell(CellState::Obstacle) {}

void ObstacleCell::setState(CellState) {}

void ObstacleCell::setNextState(CellState) {}

void ObstacleCell::updateState() {}

bool ObstacleCell::isObstacle() const {
    return true;
}
