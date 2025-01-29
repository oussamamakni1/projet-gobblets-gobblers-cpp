#include "cell.h"

Cell::Cell() : index(-1), stack() {}

Cell::Cell(const Cell &other) : index(other.index) {
    for (int i = 0; i < NB_SIZE; i++) {
        stack[i] = other.stack[i];
    }
}

bool Cell::canPush(const Piece &piece) {
    if (index == NB_SIZE - 1) {
        return false;
    }
    if (index == -1) {
        return true;
    }
    return stack[index].getSize() < piece.getSize();
}

void Cell::push(const Piece &piece) {
    if (canPush(piece)) {
        index++;
        stack[index] = piece;
    }
}

bool Cell::canPop() {
    return index != -1;
}

Piece Cell::pop() {
    if (canPop()) {
        Piece temp = stack[index];
        stack[index] = Piece(); 
        index--;
        return temp;
    }
    return Piece(); 
}

Piece Cell::peek() {
    if (canPop()) {
        return stack[index];
    }
    return Piece(); 
}

Cell& Cell::operator=(const Cell &other) {
    if (this != &other) {
        index = other.index;
        for (int i = 0; i < NB_SIZE; i++) {
            stack[i] = other.stack[i];
        }
    }
    return *this;
}
