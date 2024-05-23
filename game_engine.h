#ifndef BATTLESHIP_H
#define BATTLESHIP_H
#include <string>
#include <utility>


using namespace std;

extern bool CONFIRM_NEXT_TURN;
extern bool AUTO_PLACEMENT;
extern bool CONTINUOUS_TURNS;
extern bool CONFIRM_AI_NEXT_TURN;




void confirmNextTurn();
void confirmAINextTurn();
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
    char simBoard[10][10];
    int validCoords[10][10];

    string missingShips[7];
    int portaerei;
    int corazzata;
    int incrociatore;
    int cacciatorpediniere;
    int cacciatorpedinierex;
    int sottomarino;
    int sottomarinox;
    bool hitCells[10][10] = { false };


    // Funzioni private per l'inizializzazione
    void initBoard(char board[10][10]);
    void initPlayer(Player &player);
    void initCoords(Player* player);
    void initSimulation(Player *player);


public:
    Player();
    Player(const int playerNumber, const string &playerName);
    void stampa(char M[10][10]);
    void stampaBoardAndMem(Player *player);
    string scegliNave(Player *player);
    bool isHorizontal(int row, int col, char type, int shipLength) const;
    void HandlePlacement(Player *player, const string &shiptype);
    char strikeBoard(Player *player, Player *enemy);
    string isSank(Player *player, Player *enemy) const;
    static bool alreadyMissing(const Player *player, string name);
    void turno(Player *player, Player *enemy);
    bool checkWin(const Player *player);
    static void startGame();
    void autoPlacement(Player *player);
    void stampaBoard() const;
    void stampaBoardMem() const;
    void stampaBoardSunk() const;
    char AIstrikeBoard(Player *player, Player *enemy) ;
    void aiturno(Player *player, Player *enemy) ;
    friend void gameLoop(Player *player1, Player *player2);
    friend void AigameLoop(Player *player1, Player *player2);
    void AistartGame();
    void montecarloSim(Player *player) ;
    void bestMove(Player *player, int &x, int &y);
    void AIautoPlacement(Player *player);
    void testAI();
    bool AIHandlePlacement(Player *player, const string &type, int x, int y, const string &config);

    bool huntMode;
    int lastHitX, lastHitY;

};

string lowerString(const string &str);
int shipSize(const string &tipo);
char getChar(const string &name);
string getString(const char name);
string getOrientation();
void replace(char board[10][10], const char replacedChar, const char newChar);
void gameLoop(Player *player1, Player *player2);
void AigameLoop(Player *player1, Player *player2);
int getRandCoords();
string getRandConfig() ;


#endif // BATTLESHIP_H

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Navi
- 1 portaerei (5 celle)                         P ///
- 1 corazzata (4 celle)                         C ///
- 1 incrociatore (3 celle)                      I ///
- 1 cacciatorpediniere (3 celle ciascuno)       D ///
- 1 cacciatorpedinierex (3 celle ciascuno)      N ///
- 1 sottomarino (2 cella ciascuno)              S ///
- 1 sottomarinox (2 cella ciascuno)             R ///

CARATTERI
- Nave: `O`
- Acqua: `~`
- Colpito: `X`
- NaveColpita= `@`
- NaveAffondata= `#`
*/


//TODO UPDATE RULES
//TODO UPDATE MAIN MENU
//TODO ASAP NUOVO CONSTRUTTORE PER AI
//TODO DICE AFFONDATO SOTTOMARINOX -> FIXED
//TODO QUANDO METTO LE NAVI AUTO NON LO CHIEDE AD ENTRAMBI I PLAYER E NON DICE IL NOME -> FIXED
