#include "piece.h"

Piece::Piece() : owner(NO_PLAYER), size(NONE) {}

Piece::Piece(Player owner, Size size) : owner(owner), size(size) {}

Piece::Piece(const Piece& other) : owner(other.owner), size(other.size) {}

Player Piece::getOwner() const {
	return owner;
}

Size Piece::getSize() const {
	return size;
}

Piece& Piece::operator=(const Piece& other) {
	owner = other.owner;
	size = other.size;
	return *this;
}