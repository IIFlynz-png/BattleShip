#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

void clearScreen();


class Player {
private:
    int number;
    string name;
    char board[10][10];
    char boardMem[10][10];
    char boardSunk[10][10];
    string missingShips[7];
    int portaerei;
    int corazzata;
    int incrociatore;
    int cacciatorpediniere;
    int cacciatorpedinierex;
    int sottomarino;
    int sottomarinox;

    // Funzioni private per l'inizializzazione
    void initBoard(char board[10][10]);
    void initPlayer(Player &player);

public:
    Player();
    Player(const int playerNumber, const string &playerName);
    void stampa(char M[10][10]);
    string scegliNave(Player *player);
    void HandlePlacement(Player *player, const string &shiptype);
    void strikeBoard(Player *player, Player *enemy);
    string isSank(Player *player) const;
    static bool alreadyMissing(const Player *player, const string &name);
    void turno(Player *player, Player *enemy);
    bool checkWin(const Player *player);
    static void startGame();

    friend void gameLoop(Player *player1, Player *player2);
};

string lowerString(const string &str);
int shipSize(const string &tipo);
char getChar(const string &name);
string getString(const char name);
string getOrientation();
void replace(char board[10][10], const char replacedChar, const char newChar);
void gameLoop(Player *player1, Player *player2);

#endif // BATTLESHIP_H