#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <chrono>
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

extern bool CONFIRM_NEXT_TURN;
extern bool AUTO_PLACEMENT;
extern bool CONTINUOUS_TURNS;


void confirmNextTurn();
void clearScreen();
void displayMenu();
void displayRules();
void displaySettings();
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
    void stampaBoardAndMem(Player *player);
    string scegliNave(Player *player);
    bool isHorizontal(int row, int col, char type, int shipLength) const;
    void HandlePlacement(Player *player, const string &shiptype);
    char strikeBoard(Player *player, Player *enemy);
    string isSank(Player *player) const;
    static bool alreadyMissing(const Player *player, const string &name);
    void turno(Player *player, Player *enemy);
    bool checkWin(const Player *player);
    static void startGame();
    void autoPlacement(Player *player);
    void stampaBoard() const;
    void stampaBoardMem() const;
    void stampaBoardSunk() const;
    friend void gameLoop(Player *player1, Player *player2);

};

string lowerString(const string &str);
int shipSize(const string &tipo);
char getChar(const string &name);
string getString(const char name);
string getOrientation();
void replace(char board[10][10], const char replacedChar, const char newChar);
void gameLoop(Player *player1, Player *player2);
int getRandCoords();
string getRandConfig() ;

#endif // BATTLESHIP_H

//TODO DICE AFFONDATO SOTTOMARINOX
// QUANDO METTO LE NAVI AUTO NON LO CHIEDE AD ENTRAMBI I PLAYER E NON DICE IL NOME
