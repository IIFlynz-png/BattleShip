#include "game_engine.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

string shiplist[7] = {
    "portaerei","corazzata",   "incrociatore", "cacciatorpediniere",
    "cacciatorpedinierex", "sottomarino", "sottomarinox"};

string lowerString(const string &str) {
  string result = str;
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

void clearScreen() {
  for (int i = 0 ; i < 100 ; i++)
    cout << endl ;
}

// SETTERS & GETTERS
int shipSize(const string &tipo) {

  if (tipo == "portaerei") {
    return 5;
  } else if (tipo == "corazzata") {
    return 4;
  } else if (tipo == "incrociatore") {
    return 3;
  } else if (tipo == "cacciatorpediniere" || tipo == "cacciatorpedinierex") {
    return 3;
  } else if (tipo == "sottomarino" || tipo == "sottomarinox") {
    return 2;
  }

  return -1;
}

char getChar(const string &name) {
  if (name == "portaerei") {
    return 'P';
  } else if (name == "corazzata") {
    return 'C';
  } else if (name == "incrociatore") {
    return 'I';
  } else if (name == "cacciatorpediniere") {
    return 'D';
  } else if (name == "cacciatorpedinierex") {
    return 'N';
  } else if (name == "sottomarino") {
    return 'S';
  } else if (name == "sottomarinox") {
    return 'R';
  }
  return '!';
}

string getString(const char name) {
  if (name == 'P') {
    return "portaerei";
  } else if (name == 'C') {
    return "corazzata";
  } else if (name == 'I') {
    return "incrociatore";
  } else if (name == 'D') {
    return "cacciatorpediniere";
  } else if (name == 'N') {
    return "cacciatorpedinierex";
  } else if (name == 'S') {
    return "sottomarino";
  } else if (name == 'R') {
    return "sottomarinox";
  }
  return "error";
}

string getOrientation() {
  string orientation;
  do {
    cout <<"Capitano! Desidera posizionare la nave in orizzontale o in verticale ? : ";
    cin >> orientation;
    cout << endl;
    orientation = lowerString(orientation);
  } while (orientation != "verticale" && orientation != "orizzontale");
  return orientation;
}

void Player::stampaBoardAndMem(Player *player) {
  // Stampa la mappa del giocatore
  cout << "La tua mappa:" << endl;
  cout << "   ";
  for (int c = 0; c < 10; c++) {
    cout << " " << c;
  }
  cout << endl;
  cout << "  ";
  for (int i = 0; i < 10; i++) {
    cout << "===";
  }
  cout << "===" << endl;

  for (int i = 0; i < 10; i++) {
    cout << i << " ";
    cout << "|";
    for (int j = 0; j < 10; j++) {
      cout << " " << player->board[i][j];
    }
    cout << " |" << endl;
  }

  cout << "  ";
  for (int i = 0; i < 10; i++) {
    cout << "===";
  }
  cout << "===" << endl;

  // Stampa la mappa della memoria del giocatore
  cout << "Cosa sappiamo sull'avversario:" << endl;
  cout << "   ";
  for (int c = 0; c < 10; c++) {
    cout << " " << c;
  }
  cout << endl;
  cout << "  ";
  for (int i = 0; i < 10; i++) {
    cout << "===";
  }
  cout << "===" << endl;

  for (int i = 0; i < 10; i++) {
    cout << i << " ";
    cout << "|";
    for (int j = 0; j < 10; j++) {
      cout << " " << player->boardMem[i][j];
    }
    cout << " |" << endl;
  }

  cout << "  ";
  for (int i = 0; i < 10; i++) {
    cout << "===";
  }
  cout << "===" << endl;
}


// player INTERFACE
void Player::stampa(char M[10][10]) { // Aiuto del signor GPT in questa parte per lo stile
  clearScreen();
  cout << "   "; // Stampa uno spazio per allineare i numeri delle colonne
  for (int c = 0; c < 10; c++) {
    cout << " " << c; // Stampa uno spazio prima del numero della colonna
  }
  cout << endl;
  cout << "  "; // Stampa due spazi per allineare la prima colonna
  for (int i = 0; i < 10; i++) {
    cout << "==="; // Stampa i separatori delle colonne
  }
  cout << "===" << endl; // Stampa un separatore aggiuntivo alla fine della riga

  for (int i = 0; i < 10; i++) {
    cout << i << " "; // Stampa il numero della riga con uno spazio dopo
    cout << "|";      // Stampa il separatore di riga
    for (int j = 0; j < 10; j++) {
      cout << " "
           << M[i][j]; // Stampa uno spazio prima del contenuto della casella
    }
    cout << " |" << endl; // Stampa il separatore di riga e va a capo
  }

  cout << "  "; // Stampa due spazi per allineare la prima colonna
  for (int i = 0; i < 10; i++) {
    cout << "==="; // Stampa i separatori delle colonne
  }
  cout << "===" << endl; // Stampa un separatore aggiuntivo alla fine della riga
}

// PRIVATE METHODS
void Player::initBoard(char board[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      board[i][j] = '~';
    }
  }
}

void Player::initPlayer(Player &player) {
  for (int i = 0; i < 7; i++) player.missingShips[i] = "O";
  player.portaerei = 1;
  player.corazzata = 1;
  player.incrociatore = 1;
  player.cacciatorpediniere = 1;
  player.cacciatorpedinierex = 1;
  player.sottomarino = 1;
  player.sottomarinox = 1;
}

// CONSTRUCTORS
Player::Player() {
  initBoard(board);
  initBoard(boardMem);
  initBoard(boardSunk);
  initPlayer(*this); // This is used to pass the current object
}

Player::Player(const int playerNumber, const string &playerName) {
  number = playerNumber;
  name = playerName;
  initBoard(board);
  initBoard(boardMem);
  initBoard(boardSunk);
  initPlayer(*this); // This is used to pass the current object
}

// PUBLIC METHODS

string Player::scegliNave(Player *player) {
  string nome;
  bool naveValida = false; // Flag per controllare se la nave è valida

  cout << "Quale nave posizioniamo, capitano?" << endl;
  cout << "Portaerei"
       << " (Rimanenti: " << this->portaerei << ")" << endl;
  cout << "Corazzata"
       << " (Rimanenti: " << this->corazzata << ")" << endl;
  cout << "Incrociatore"
       << " (Rimanenti: " << this->incrociatore << ")" << endl;
  cout << "Sottomarino"
       << " (Rimanenti: " << this->sottomarino + this->sottomarinox << ")"
       << endl;
  cout << "Cacciatorpediniere"
       << " (Rimanenti: "
       << this->cacciatorpediniere + this->cacciatorpedinierex << ")" << endl;

  do {
    cout << "Inserisca il nome della nave: ";
    cin >> nome;
    nome = lowerString(nome);

    if (nome != "portaerei" && nome != "corazzata" && nome != "incrociatore" &&
        nome != "sottomarino" && nome != "cacciatorpediniere") {
      cout << "Capitano, si e' percaso ubriacato, non abbiamo questa nave!"
           << endl;
      cout << "Inserisca un nome valido." << endl << endl;
    } else if ((nome == "portaerei" && this->portaerei == 0) ||
               (nome == "corazzata" && this->corazzata == 0) ||
               (nome == "incrociatore" && this->incrociatore == 0) ||
               (nome == "sottomarino" && this->sottomarino == 0 &&
                this->sottomarinox == 0) ||
               (nome == "cacciatorpediniere" && this->cacciatorpediniere == 0 &&
                this->cacciatorpedinierex == 0)) {
      cout << "Mi dispiace, capitano. Non abbiamo più " << nome
           << " a disposizione." << endl;
    } else { // Nave valida
      naveValida = true;
    }
  } while (!naveValida); // Continua a chiedere finché non viene inserita una nave valida

  // Aggiorna il numero di navi rimanenti solo se la nave è valida
  if (nome == "portaerei") {
    this->portaerei--;
  } else if (nome == "corazzata") {
    this->corazzata--;
  } else if (nome == "incrociatore") {
    this->incrociatore--;
  } else if (nome == "sottomarino") {
    if (this->sottomarino > 0) {
      this->sottomarino--;
    } else {
      this->sottomarinox--;
    }
  } else if (nome == "cacciatorpediniere") {
    if (this->cacciatorpediniere > 0) {
      this->cacciatorpediniere--;
    } else {
      this->cacciatorpedinierex--;
    }
  }

  return nome;
}

void Player::HandlePlacement(Player *player, const string &shiptype) {
    // Ottengo delle coordinate valide
    string config = getOrientation();
    int x, y;
    char type = getChar(shiptype);
    bool validCoords = false;
    int lenght = shipSize(shiptype);

    while (!validCoords) {
        cout << "Inserisci la coordinata x della nave (0-9): ";
        cin >> x;
        cout << "Inserisci la coordinata y della nave (0-9): ";
        cin >> y;

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            bool isOverlapping = false;
            if (config == "verticale") {
                if (x + lenght < 10) { // Controllo corretto per il limite verticale
                    for (int i = 0; i < lenght; i++) {
                        if (this->board[x + i][y] != '~') {
                            isOverlapping = true;
                            break;
                        }
                    }
                    if (!isOverlapping) {
                        validCoords = true;
                    } else {
                        cout << "Le coordinate inserite sono già occupate da un'altra nave. Reinserisci le coordinate." << endl;
                    }
                } else {
                    cout << "La nave eccede i limiti della griglia in verticale. Reinserisci le coordinate." << endl;
                }
            } else if (config == "orizzontale") {
                if (y + lenght < 10) { // Controllo corretto per il limite orizzontale
                    for (int i = 0; i < lenght; i++) {
                        if (this->board[x][y + i] != '~') {
                            isOverlapping = true;
                            break;
                        }
                    }
                    if (!isOverlapping) {
                        validCoords = true;
                    } else {
                        cout << "Le coordinate inserite sono già occupate da un'altra nave. Reinserisci le coordinate." << endl;
                    }
                } else {
                    cout << "La nave eccede i limiti della griglia in orizzontale. Reinserisci le coordinate." << endl;
                }
            }
        } else {
            cout << "Coordinate non valide. Inserisci valori tra 0 e 9." << endl;
        }
    }

    // Piazzare la nave sulla griglia
    if (config == "orizzontale") {
        for (int i = 0; i < lenght; i++) {
            this->board[x][y + i] = 'O'; // Posizionamento orizzontale corretto
            this->boardSunk[x][y + i] = type;
        }
    } else if (config == "verticale") {
        for (int i = 0; i < lenght; i++) {
            this->board[x + i][y] = 'O'; // Posizionamento verticale corretto
            this->boardSunk[x + i][y] = type;
        }
    }
}


void Player::strikeBoard(Player *player, Player *enemy) {
  // Scelta le coordinate
  int x, y;
  do {
    cout << "Dove spariamo signor capitano (Inserisci la riga e poi la colonna) ? "
         << endl;
    cin >> x >> y;
    if (x > 9 or x < 0 or y > 9 or y < 0)
      cout << "Capitano si sarà mica ubriacato! Non possiamo sparare là !"
           << endl;
  } while (x > 9 or x < 0 or y > 9 or y < 0);

  // STRIKES HANDLING
  if (enemy->board[x][y] == 'O') { // CASE 1 PLAYER HITS THE TARGET
    // Gestiamo tutte le board
    enemy->board[x][y] = '@';
    this->boardMem[x][y] = '@';
    enemy->boardSunk[x][y] = '@';
    // Comunicazione al giocatore
    cout << "BINGO! Ha fatto centro signor capitano " << endl;
  } else if (enemy->board[x][y] == '~') { // CASE 2 PLAYER HITS WATER
    enemy->board[x][y] = 'X';
    this->boardMem[x][y] = 'X';
    // Comunicazione col giocatore
    cout << "DANNAZIONE! Abbiamo colpito il mare signor capitano " << endl;
  } else if (enemy->board[x][y] =='@') { // CASE 3 PLAYER HITS A SUNKEN PORTION OF A SHIP
    cout << "SIGNORE CHE COSA FA ?!!?! Abbiamo gia affondato quella porzione di nave, spari altrove !"
         << endl;
  } else { // CASE 4 PLAYER HITS AN ALREADY SHOT PORTION OF WATER
    cout << "SIGNORE CHE COSA FA ?!!?! Abbiamo gia visto che non c'e un bel niente in quel punto, spari altrove !"
         << endl;
  }
}

// INIZIALIZZA LA LISTA-SPARITI USA IL COSTRUTTORE

// FUNZIONE PER SAPERE SE UNA NAVE E' GIA' STATA AFFONDATA
bool Player::alreadyMissing(const Player *player, const string &name) {
  for (int i = 0; i < 7; i++) {
    if (player->missingShips[i] == name) {
      return true;
    }
  }
  return false;
}

// FUNZIONE PER SOSTITUIRE UN CHAR CON UN ALTRO NELLA MATRICE
void replace(char board[10][10], const char replacedChar, const char newChar) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if (board[i][j] == replacedChar) {
        board[i][j] = newChar;
      }
    }
  }
}



// FUNZIONE PER CONTROLLARE SE UNA NAVE SAREBBE AFFONDATA
string Player::isSank(Player *player) const {
  // LOOKING FOR SOMETHING MISSING
  for (int i = 0; i < 7; i++) {
    string ship = shiplist[i];
    char type = getChar(ship);
    // CHECK IF THE SHIP WE ARE CONTROLLING IS ALREADY SUNKEN
    if (!player->alreadyMissing(player, ship)) {
      int found = 0;
      for (int righe = 0; righe < 10; righe++) {
        for (int colonne = 0; colonne < 10; colonne++) {
          if (this->boardSunk[righe][colonne] == type) {
            found++;
          }
        }
      }
      // IF SHIP HAS BEEN SUNKED
      if (found == 0) {
        // HANDLE PLAYER BOARDS CHAR REPLACEMENT
        replace(player->board, type, '#');
        replace(player->boardSunk, type, '#');

        // UPDATE THE MISSING LIST
        for (int j = 0; j < 7; j++) {
          if (this->missingShips[j] == "O") {
            player->missingShips[j] = ship;
            return ship;
          }
        }
      }
    }
  }
  return "error";
}

// UPDATE HEADER FILE

// FUNZIONE PER VERIFICARE LA VINCITA
bool Player::checkWin(const Player *player) {
  // CHECK IF ALL SHIPS ARE SUNKEN
  for (int i = 0 ; i < 7; i++) {
    if (player->missingShips[i] == "O") { // INIZIALMENTENE VOLEVO CONTROLLARE TUTTA LA MATRICE MA POI HO UTILIZZATO QUESTO METODO
      return false;
    }
  }
  return true;
}


void Player::turno(Player *player, Player *enemy) {

  string sunkenOne = "";
  cout << "TURNO DEL GIOCATORE: " << player->name << endl;

  // Utilizzare la nuova funzione per stampare entrambe le mappe
  player->stampaBoardAndMem(player);

  player->strikeBoard(player, enemy);

  sunkenOne = player->isSank(enemy);
  if (sunkenOne != "error") {
    cout << "Abbiamo affondato questa imbarcazione: " << sunkenOne << "!" << endl;
  }

  if (player->checkWin(enemy)) {
    cout << "Congratulazioni, " << player->name << "! Hai vinto la partita!" << endl;
    return;
  }

  cout << "Fine del turno di " << player->name << "." << endl;
  cout << "-----------------------------------" << endl;
}

void gameLoop(Player *player1, Player *player2) {
    clearScreen();
    bool game_over = false;
    Player *current_player = player1;
    Player *opponent = player2;

    while (!game_over) {
        // Turno del giocatore corrente
        current_player->turno(current_player, opponent);

        // Scambio dei ruoli dei giocatori per il turno successivo
        swap(current_player, opponent);

        // Verifica se la partita è finita
        if (current_player->checkWin(opponent)) {
            cout << "Partita finita! " << current_player->name << " ha vinto!" << endl;
            game_over = true;
        }
    }
}

void Player::startGame() {
    char answer;
    // Creazione dei giocatori
    Player player1(1, "Player 1");
    Player player2(2, "Player 2");

    // Presentazione delle istruzioni del gioco
    cout << "Benvenuti al gioco della battaglia navale!" << endl;
    cout << "I giocatori si alterneranno per posizionare le proprie navi sulla griglia." << endl;
    cout << "Una volta posizionate le navi, inizia il gioco e i giocatori si alterneranno nei turni per cercare di colpire le navi nemiche." << endl;
    cout << "Il primo giocatore a affondare tutte le navi dell'avversario vince il gioco." << endl;
    cout << "Pronti alla battaglia signori ? (Y)" << endl;
    cin >> answer;
    clearScreen();

    // Inizio del gioco
    cout << "Inizia il posizionamento delle navi per il Player 1" << endl;
    for (int i = 0; i < 7; ++i) {
        string shipType = player1.scegliNave(&player1);
        player1.HandlePlacement(&player1, shipType);
        player1.stampa(player1.board);
    }
    clearScreen();  // Clear screen to prevent Player 2 from seeing Player 1's board

    cout << "Inizia il posizionamento delle navi per il Player 2" << endl;
    for (int i = 0; i < 7; ++i) {
        string shipType = player2.scegliNave(&player2);
        player2.HandlePlacement(&player2, shipType);
        player2.stampa(player2.board);
    }

    // Avvio del loop di gioco
    gameLoop(&player1, &player2);
}




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
