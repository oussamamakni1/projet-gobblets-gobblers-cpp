#include <iostream>
#include <string>
#include "board.h"

using namespace std;
 
void tour_joueur(Player currentPlayer);
Size taille_piece(int c);

int main()
{   
    char action; int l1; int c1; int l2; int c2; int s; 
    int Mode_jeu;
    StatusEnum status;
    Player winner;

    Board* game = new Board(); 
    Player currentPlayer = PLAYER_1;

    cout << endl << "\033[1;31m" << "bienvenue dans le jeu Gobblets-Gobblesrs!" << "\033[0m" << endl;
    cout << endl;
    cout << "\033[1;32m" << "  1 : jouer 1 contre 1" << "\033[0m" << endl;
    cout << "\033[1;32m" << "  2 : Quitter" << "\033[0m" << endl;
    cout << endl << "\033[1m" << "Entrer le Choix : " << "\033[0m";
    cin >> Mode_jeu;
    if (Mode_jeu == 2) {
        return 0;
    }
    else if (Mode_jeu == 1) {
        tour_joueur(currentPlayer);
        cout << *game << endl;

        do {


            winner = game->getWinner();

            if (winner != NO_PLAYER) {
                switch (winner) {
                case PLAYER_1:
                    cout << "Player 1 gagne!" << endl;
                    break;
                case PLAYER_2:
                    cout << "Player 2 gagne!" << endl;
                    break;
                default:
                    break;
                }
                return 0;
            }


            std::cout << "Action choice. " << "\033[1;33m" << "1: Placer, 2: deplacer, q:Quitter" <<"\033[0m"<< std::endl;
            std::cin >> action;
            while (action != '1' && action != '2' && action != 'q') {
				cout << "\033[0;31m" << "entré invalid. réessayer." << "\033[0m" << endl;
				cin >> action;
			}

            if (action == 'q')
                return 0;
            if (action == '1') {
                cout << "Choisir piece à placer. " << "\033[1;33m" << "1: petit, 2:moyenne, 3: grand, 4: Annullé" << "\033[0m" << endl;
                cin >> s;
                if (s != 1 && s != 2 && s != 3 && s != 4) {
                    cout << "\033[0;31m" << "entré invalid. réessayer." << "\033[0m" << endl;
                    continue;
                }
                else if (s == 4) {
                    continue;
                }
                else {
                    if (game->getNbPiecesInHouse(currentPlayer, taille_piece(s)) == 0) {
                        cout << "\033[0;31m" << "Pas encore des pieces de ce taille. réessayer." << "\033[0m" <<endl;
                        continue;
                    }
                    else {
                        cout << "**Entrez la ligne de la case dans laquelle vous voulez placer votre pièce 1->3 :" << endl;
                        cin >> l1;
                        cout << "**Entrez la colonne de la case dans laquelle vous voulez placer votre pièce 1->3 :" << endl;
                        cin >> c1;
                        status = game->placePiece(currentPlayer, taille_piece(s), l1, c1);
                        cout <<endl<< "Taille sélectionnée : " << taille_piece(s) << endl;

                        if (status != OK) {
                            cout << "\033[0;31m" << "entré invalid. réessayer." << "\033[0m" << endl;
                            continue; 
                        }
                        else {
                            currentPlayer = game->nextPlayer(currentPlayer);
                            tour_joueur(currentPlayer);
                            cout << *game << endl;
                        }
                    }
                }
            }
            else if (action == '2') {
                cout << "**Entrez la ligne de la pièce que vous voulez déplacer 1->3 :" << endl;
                cin >> l1;
                cout << "**Entrez la colonne de la pièce que vous voulez déplacer 1->3 :" << endl;
                cin >> c1;
                if (game->getPlaceHolder(l1, c1) != currentPlayer && game->getPlaceHolder(l1, c1) != NO_PLAYER) {
                    cout << "\033[0;31m" << "Vous ne pouvez pas déplacer cette pièce. Veuillez réessayer." << "\033[0m" << endl;
                }
                else {
                    cout << "**Entrez la ligne de la case vers laquelle vous voulez déplacer votre pièce :" << endl;
                    cin >> l2;
                    cout << "**Entrez la colonne de la case vers laquelle vous voulez déplacer votre pièce :" << endl;
                    cin >> c2;
                    status = game->movePiece(currentPlayer, l1, c1, l2, c2);
                    if (status == OK) {
                        currentPlayer = game->nextPlayer(currentPlayer);
                        tour_joueur(currentPlayer);
                        cout << *game << endl;
                    }
                    else {
                        cout << "\033[0;31m" << "entré invalid. réessayer." << "\033[0m" << endl;
                    }
                }
            }
        } while (true);
        return 0;
    }

}

void tour_joueur(Player currentPlayer) {
    cout << endl;
    if (currentPlayer == PLAYER_1)
        cout << "\033[1;94m" << "tour" << "\033[0m" <<"\033[32m"<< " Player 1 :" <<"\033[0m"<< endl<<endl;
    else if (currentPlayer == PLAYER_2)
        cout << "\033[1;94m" << "tour" << "\033[0m" <<"\033[32m"<< " Player 2 :" <<"\033[0m"<< endl<<endl;
}


Size taille_piece(int c) {
    switch (c)
    {
    case 1:
        return SMALL;
    case 2:
        return MEDIUM;
    case 3:
        return LARGE;
    default:
        return NONE;
    }
}

