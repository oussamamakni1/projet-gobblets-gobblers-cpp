#include "board.h" 
 

Board::Board() {
	for (int i = 0; i < NB_SIZE; i++) {
		p1Pieces[i] = NB_INITIAL_PIECES;
		p2Pieces[i] = NB_INITIAL_PIECES;
	}
}
 
 
Board::Board(const Board& board){ 
     
    for (int i = 0; i < NB_SIZE; i++) { 
        p1Pieces[i] = board.p1Pieces[i]; 
        p2Pieces[i] = board.p2Pieces[i]; 
    }
     
    for (int i = 0; i < DIMENSIONS; i++) { 
        for (int j = 0; j < DIMENSIONS; j++) { 
            state[i][j] = board.state[i][j]; 
        } 
    } 
 
     
} 
 
 
Board::~Board() { 

 
} 
// Méthodes privées 
Cell& Board::getCellAt(int line, int column) { 
return state[line][column]; 
} 
int* Board::getHousesOfPlayer(Player player) { 
return (player == PLAYER_1) ? p1Pieces : p2Pieces; 
} 
Player Board::nextPlayer(Player currentPlayer) const { 
return (currentPlayer == PLAYER_1) ? PLAYER_2 : PLAYER_1; 
} 
// Méthodes publiques 
Player Board::getPlaceHolder(int line, int column) {
	return state[line-1][column-1].peek().getOwner();
} 
Size Board::getPieceSize(int line, int column) {
	return state[line-1][column-1].peek().getSize();
}
int Board::getNbPiecesInHouse(Player checkedPlayer, Size pieceSize) {
	if(checkedPlayer == PLAYER_1) {
		return p1Pieces[pieceSize - 1];
	}else if(checkedPlayer == PLAYER_2) {
		return p2Pieces[pieceSize - 1];
	}else {
		return 0;
	}
} 
StatusEnum Board::placePiece(Player currentPlayer, Size pieceSize, int line, int column) {
	Piece piece(currentPlayer, pieceSize);
	if(line < 1 || line > 3 || column < 1 || column > 3) {
		return INVALID_ENTRY;
	}
	if(getNbPiecesInHouse(currentPlayer, pieceSize) == 0) {
		return INVALID_SOURCE;
	}
	if(pieceSize <= getPieceSize(line, column)) {
		return INVALID_TARGET;
	}
	if (state[line-1][column-1].canPush(piece) == true) {
		state[line-1][column-1].push(piece);
		if (currentPlayer == PLAYER_1) {
			p1Pieces[pieceSize - 1]--;
		}
		else if (currentPlayer == PLAYER_2) {
			p2Pieces[pieceSize - 1]--;
		}
		return OK;
	}
	else {
		return INVALID_TARGET;
	}
}
 
StatusEnum Board::movePiece(Player currentPlayer, int sourceLine, int sourceColumn, int targetLine, int 
targetColumn) { 
    if (sourceLine < 1 || sourceLine > DIMENSIONS || sourceColumn < 1 || 
sourceColumn > DIMENSIONS || 
        targetLine < 1 || targetLine > DIMENSIONS || targetColumn < 1 || targetColumn 
> DIMENSIONS) { 
        return INVALID_ENTRY; 
    } 
 
    if (getPlaceHolder(sourceLine, sourceColumn) != currentPlayer) { 
        return INVALID_SOURCE; 
    } 
 
    if (getPieceSize(sourceLine, sourceColumn) <= getPieceSize(targetLine, targetColumn)) {
		return INVALID_TARGET;
	}

	Piece piece = state[sourceLine-1][sourceColumn-1].peek();
	if (state[targetLine-1][targetColumn-1].canPush(piece) == true) {
		state[sourceLine-1][sourceColumn-1].pop();
		state[targetLine-1][targetColumn-1].push(piece);
		return OK;
	}
	else {
		return INVALID_TARGET;
	} 
} 
 
Player Board::getWinner() { 
    for (int i = 1; i <= 3; i++) { 
        
        if (getPlaceHolder(i, 1) == getPlaceHolder(i, 2) && getPlaceHolder(i, 2) == getPlaceHolder(i, 3)) { 
            return getPlaceHolder(i, 3); 
        } 
        
        if (getPlaceHolder(1, i) == getPlaceHolder(2, i) && getPlaceHolder(2, i) == getPlaceHolder(3, i)) { 
            return getPlaceHolder(3, i); 
        } 
    } 
    
    if (getPlaceHolder(1, 1) == getPlaceHolder(2, 2) && getPlaceHolder(2, 2) == getPlaceHolder(3, 3)) { 
        return getPlaceHolder(3, 3); 
    } 
    
    if (getPlaceHolder(1, 3) == getPlaceHolder(2, 2) && getPlaceHolder(2, 2) == getPlaceHolder(3, 1)) { 
        return getPlaceHolder(3, 1); 
    } 
    return NO_PLAYER; 
}

 
std::ostream& Board::printHouses(std::ostream& stream, Player player) {
    int* houses = getHousesOfPlayer(player);
    stream << "Player " << (player == PLAYER_1 ? "1" : "2") << "'s pieces:\n";
    for (int i = 0; i < NB_SIZE; i++) {
        stream << "Size " << (i + 1) << ": " << houses[i] << "\n";
    }
    return stream;
}

std::ostream& operator<<(std::ostream& stream, Board& board) {
    
    int* housesPlayer1 = board.getHousesOfPlayer(PLAYER_1);
    int* housesPlayer2 = board.getHousesOfPlayer(PLAYER_2);
    std::string SMALLp1 = "";
    std::string SMALLp2 = "";
    std::string MEDIUMp1 = "";
    std::string MEDIUMp2 = "";
    std::string LARGEp1 = "";
    std::string LARGEp2 = "";
    stream << "Player 1's pieces:   |  Player 2's pieces:" << std::endl;
    for (int i = 0; i < NB_SIZE; i++) {
        if (i==0){
            if (housesPlayer1[i]==0){
                SMALLp1 = " ";
            }
            else{
                for (int j=1; j<= housesPlayer1[i];j++ ){
                SMALLp1 += "x ";}
            }
            if (housesPlayer2[i]==0){
                SMALLp2 = " ";
            }
            else{
                for (int j=1; j<= housesPlayer2[i];j++ ){
                SMALLp2 += ". ";}
            }       
        stream << "   Size " << (i + 1) << ": " <<"\033[33m"<< SMALLp1
               <<"\033[0m"<< "         |     Size " << (i + 1) << ": " <<"\033[95m"<< SMALLp2 <<"\033[0m"<< std::endl;
        }
        if (i==1){
        if (housesPlayer1[i]==0){
                MEDIUMp1 = " ";
            }
            else{
                for (int j=1; j<= housesPlayer1[i];j++ ){
                MEDIUMp1 += "X ";}
            }
            if (housesPlayer2[i]==0){
                MEDIUMp2 = " ";
            }
            else{
                for (int j=1; j<= housesPlayer2[i];j++ ){
                MEDIUMp2 += "o ";}
            }
        stream << "   Size " << (i + 1) << ": " <<"\033[33m"<< MEDIUMp1
               <<"\033[0m"<< "         |     Size " << (i + 1) << ": " <<"\033[95m"<< MEDIUMp2 <<"\033[0m"<< std::endl;
        }
        if(i==2){
        if (housesPlayer1[i]==0){
                LARGEp1 = " ";
            }
            else{
                for (int j=1; j<= housesPlayer1[i];j++ ){
                LARGEp1 += "# ";}
            }
            if (housesPlayer2[i]==0){
                LARGEp2 = " ";
            }
            else{
                for (int j=1; j<= housesPlayer2[i];j++ ){
                LARGEp2 += "O ";}
            }
        stream << "   Size " << (i + 1) << ": " <<"\033[33m"<< LARGEp1
               <<"\033[0m"<< "         |     Size " << (i + 1) << ": " <<"\033[95m"<< LARGEp2 <<"\033[0m"<< std::endl;
        }
    }

    
    stream << std::endl;

    
    for (int i = 0; i < DIMENSIONS; i++) {
        for (int j = 0; j < DIMENSIONS; j++) {
            Piece piece = board.getCellAt(i, j).peek();
            char displayChar;

            if (piece.getOwner() == PLAYER_1) {
                switch (piece.getSize()) {
                    case SMALL:
                        displayChar = SMALLP1;
                        break;
                    case MEDIUM:
                        displayChar = MEDIUMP1;
                        break;
                    case LARGE:
                        displayChar = LARGEP1;
                        break;
                    default:
                        displayChar = ' ';
                        break;
                }
            } else if (piece.getOwner() == PLAYER_2) {
                switch (piece.getSize()) {
                    case SMALL:
                        displayChar = SMALLP2;
                        break;
                    case MEDIUM:
                        displayChar = MEDIUMP2;
                        break;
                    case LARGE:
                        displayChar = LARGEP2;
                        break;
                    default:
                        displayChar = ' ';
                        break;
                }
            } else {
                displayChar = ' ';
            }

            stream << displayChar;
            if (j < DIMENSIONS - 1) {
                stream <<"\033[35m"<<"  |"<<"\033[0m"; // Ajouter des séparateurs de colonnes
            }
        }
        stream << std::endl;
        if (i < DIMENSIONS - 1) {
            stream <<"\033[35m"<< "---+---+---" <<"\033[0m"<< std::endl; // Ajouter des séparateurs de lignes
        }
    }

    return stream;
}


