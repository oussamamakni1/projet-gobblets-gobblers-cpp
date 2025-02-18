#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "cell.h"
#include "playerEnum.h"
#include "config.h"
#include "statusEnum.h"
#include <iostream>

class Board
{
    private:
        Cell state[DIMENSIONS][DIMENSIONS];
        int p1Pieces[NB_SIZE];
        int p2Pieces[NB_SIZE];

        Cell& getCellAt(int line, int column);
        int* getHousesOfPlayer(Player player);
    public:
        Board();
        Board(const Board& other);
        ~Board();

        Player nextPlayer(Player currentPlayer) const;
        Player getPlaceHolder(int line, int column);
        Size getPieceSize(int line, int column);
        int getNbPiecesInHouse(Player checkedPlayer, Size pieceSize);

        StatusEnum placePiece(Player currentPlayer, Size pieceSize, int line, int column);
        StatusEnum movePiece(Player currentPlayer, int sourceLine, int sourceColumn, int targetLine, int targetColumn);

        Player getWinner();

        std::ostream& printHouses(std::ostream& stream, Player player);
        friend std::ostream& operator<<(std::ostream& stream, Board& board);
};


#endif // BOARD_H