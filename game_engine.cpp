#include "game_engine.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <random>
#include <utility>
using namespace std;


////// IMPOSTAZIONI //////

bool CONFIRM_NEXT_TURN = false;   // Initial value
bool AUTO_PLACEMENT = false;    // Initial value
bool CONTINUOUS_TURNS = false;   // Initial value
bool CONFIRM_AI_NEXT_TURN = true; // Initial value

string shiplist[7] = {
    "portaerei","corazzata",   "incrociatore", "cacciatorpediniere",
    "cacciatorpedinierex", "sottomarino", "sottomarinox"};



////// INTERFACCIA //////

// Funzione per mostrare il menù
void displayMenu() {
    cout << "______         _    _                  _  _          _   _                       _       " << endl;
    cout << "| ___ \\       | |  | |                | |(_)        | \\ | |                     | |      " << endl;
    cout << "| |_/ /  __ _ | |_ | |_   __ _   __ _ | | _   __ _  |  \\| |  __ _ __   __  __ _ | |  ___ " << endl;
    cout << "| ___ \\ / _` || __|| __| / _` | / _` || || | / _` | | . ` | / _` |\\ \\ / / / _` || | / _ \\" << endl;
    cout << "| |_/ /| (_| || |_ | |_ | (_| || (_| || || || (_| | | |\\  || (_| | \\ V / | (_| || ||  __/" << endl;
    cout << "\\____/  \\__,_| \\__| \\__| \\__,_| \\__, ||_||_| \\__,_| \\_| \\_/ \\__,_|  \\_/   \\__,_||_| \\___|" << endl;
    cout << "                                 __/ |                                                   " << endl;
    cout << "                                |___/                                                    " << endl;
    cout << endl;
    cout << "------------------------------------" << endl;
    cout << "1. Regole" << endl;
    cout << "2. Gioca (Player vs Player)" << endl;
    cout << "3. Gioca (Player vs AI)" << endl;
    cout << "4. Impostazioni" << endl;
    cout << "5. Esci" << endl;
    cout << "------------------------------------" << endl;
    cout << "Seleziona un'opzione: ";
}

// Funzione per mostrare le regole di gioco
void displayRules() {
    cout << "Regole del gioco:" << endl;
    cout << "- Ogni giocatore ha una flotta di 7 navi:" << endl;
    cout << "  1 Portaerei (5 celle)" << endl;
    cout << "  1 Corazzata (4 celle)" << endl;
    cout << "  1 Incrociatore (3 celle)" << endl;
    cout << "  2 Cacciatorpedinieri (3 celle)" << endl;
    cout << "  2 Sottomarini (2 celle)" << endl;
    cout << "- Le navi possono essere posizionate orizzontalmente o verticalmente sulla griglia." << endl;
    cout << "- I giocatori si alternano sparando un colpo alla volta." << endl;
    cout << "- Se un colpo colpisce una nave, viene segnato con '@'." << endl;
    cout << "- Se un colpo colpisce l'acqua, viene segnato con 'X'." << endl;
    cout << "- Quando una nave viene affondata, tutte le sue celle vengono segnate con '#'." << endl;
    cout << "- Il primo giocatore che affonda tutte le navi dell'avversario vince il gioco." << endl;
    cout << "Premi INVIO per tornare al menu principale..." << endl;
    cin.ignore();
    string dummy;
    getline(cin, dummy);
}

// Funzione per le impostazioni
void displaySettings() {
    cout << "Impostazioni:" << endl;
    cout << "1. Conferma per il turno successivo: " << (CONFIRM_NEXT_TURN ? "Attivo" : "Disattivo") << endl;
    cout << "2. Conferma per il turno dell'IA: " << (CONFIRM_AI_NEXT_TURN ? "Attivo" : "Disattivo") << endl;
    cout << "3. Posizionamento automatico delle navi: " << (AUTO_PLACEMENT ? "Attivo" : "Disattivo") << endl;
    cout << "4. Turni continui: " << (CONTINUOUS_TURNS ? "Attivo" : "Disattivo") << endl;
    cout << "Seleziona un'opzione per modificarla (0 per uscire): ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1:
            CONFIRM_NEXT_TURN = !CONFIRM_NEXT_TURN;
        break;
        case 2:
            CONFIRM_AI_NEXT_TURN = !CONFIRM_AI_NEXT_TURN;
        break;
        case 3:
            AUTO_PLACEMENT = !AUTO_PLACEMENT;
        break;
        case 4:
            CONTINUOUS_TURNS = !CONTINUOUS_TURNS;
        break;
        case 0:
            return;
        default:
            cout << "Opzione non valida. Riprova." << endl;
        break;
    }

    displaySettings(); // Mostra nuovamente le impostazioni
}

// Funzione che ritorna la stringa in minuscolo
string lowerString(const string &str) {
  string result = str;
  transform(result.begin(), result.end(), result.begin(), ::tolower);
  return result;
}

// Funzione per fare il clear dello schermo
void clearScreen() {
  for (int i = 0 ; i < 100 ; i++)
    cout << endl ;
}

void confirmNextTurn() {
    if (CONFIRM_NEXT_TURN) {
        cout << "Premi INVIO per passare al turno successivo..." << endl;
        cin.ignore();  // Ignora i caratteri rimanenti nel buffer
        string dummy;
        getline(cin, dummy);  // Attendi l'input dell'utente
        clearScreen();
    }
}

void confirmAINextTurn() {
    if (CONFIRM_AI_NEXT_TURN) {
        cout << "Premi INVIO per passare al turno dell'IA..." << endl;
        cin.ignore();  // Ignora i caratteri rimanenti nel buffer
        string dummy;
        getline(cin, dummy);  // Attendi l'input dell'utente
    }
}




////// GETTERS //////
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
  } else if (name == 'D' || name == 'N') { // CACCIATORPEDINIERE E CACCIATORPEDINIERE X
    return "cacciatorpediniere";
  } else if (name == 'S' || name == 'R') { // SOTTOMARINO E SOTTOMARINO X
    return "sottomarino";
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




////// METODI PRIVATI //////

// Implementazione deil metodo per inizializzare una board
void Player::initBoard(char board[10][10]) {
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      board[i][j] = '~';
    }
  }
}

// implementazione del metodo per inizializzare un giocatore
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


////// COSTRUTTORI //////

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
  initPlayer(*this);
}



////// FUNZIONI PER IL GAME //////

// Implementazione del loop fi gioco principale
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

        // Verifica se la partita e' finita
        if (current_player->checkWin(opponent)) {
            cout << "Partita finita! " << current_player->name << " ha vinto!" << endl;
            game_over = true;
        }
    }
}

// Implementazione del metodo startGame per il gioco PVP
void Player::startGame() {
    char answer;

    // Creazione dei giocatori
    Player player1(1, "Player 1");
    Player player2(2, "Player 2");


    // Chiedi all'utente  1 se vuole posizionare le navi manualmente o automaticamente
    if (!AUTO_PLACEMENT) {
        cout << "Giocatore 1, vuoi posizionare le navi manualmente (M) o automaticamente (A)? ";
        cin >> answer;
        answer = tolower(answer);
    } else {
        answer = 'a'; // Imposta il posizionamento automatico se AUTO_PLACEMENT e' true
    }

    clearScreen();


    if (answer == 'm') {
        cout << "Inizia il posizionamento delle navi per il Player 1" << endl;
        for (int i = 0; i < 7; ++i) {
            string shipType = player1.scegliNave(&player1);
            player1.HandlePlacement(&player1, shipType);
            player1.stampa(player1.board);
        }
        clearScreen();  // Clear screen to prevent Player 2 from seeing Player 1's board

    } else {
        // Posizionamento automatico delle navi
        player1.autoPlacement(&player1);
    }



    // Chiedi all'utente  2 se vuole posizionare le navi manualmente o automaticamente
    if (!AUTO_PLACEMENT) {
        cout << "Giocatore 2, vuoi posizionare le navi manualmente (M) o automaticamente (A)? ";
        cin >> answer;
        answer = tolower(answer);
    } else {
        answer = 'a'; // Imposta il posizionamento automatico se AUTO_PLACEMENT e' true
    }

    clearScreen();

    if (answer == 'm') {
        cout << "Inizia il posizionamento delle navi per il Player 2" << endl;
        for (int i = 0; i < 7; ++i) {
            string shipType = player2.scegliNave(&player2);
            player2.HandlePlacement(&player2, shipType);
            player2.stampa(player2.board);
        }
    } else {
        player2.autoPlacement(&player2);
    }


    // Avvio del loop di gioco
    gameLoop(&player1, &player2);
}

// Implementazione del turno di gioco per il gioco PVP
void Player::turno(Player *player, Player *enemy) {
    string sunkenOne = "";
    cout << "TURNO DEL GIOCATORE: " << player->name << endl;

    // Utilizzare la nuova funzione per stampare entrambe le mappe
    player->stampaBoardAndMem(player);

    bool keepTurn = true; // Flag per continuare il turno

    while (keepTurn) {
        char result = player->strikeBoard(player, enemy);
        sunkenOne = player->isSank(enemy,player);
        if (sunkenOne != "error") {
            char temp = getChar(sunkenOne);
            sunkenOne = getString(temp);
            cout << "Abbiamo affondato questa imbarcazione: " << sunkenOne << "!" << endl;
        }

        // Verifica la vittoria prima di passare al turno successivo
        if (player->checkWin(enemy)) {
            cout << "Partita finita! " << player->name << " ha vinto!" << endl;
            return;
        }

        // Determina se il turno deve continuare
        if (CONTINUOUS_TURNS) {
            keepTurn = (result == '@'); // Continua se ha colpito una nave
        } else {
            keepTurn = false;
        }
    }

    cout << "Fine del turno di " << player->name << "." << endl;

    if (CONFIRM_NEXT_TURN) {
        cout << "Premi INVIO per passare al turno successivo..." << endl;
        cin.ignore();  // Ignora i caratteri rimanenti nel buffer
        string dummy;
        getline(cin, dummy);  // Attendi l'input dell'utente

        // Clear screen
        clearScreen();

        // Player 2, sei pronto?
        cout << "Player 2, sei pronto?" << endl;
        cout << "Premi INVIO per confermare..." << endl;
        getline(cin, dummy);  // Attendi l'input dell'utente
        clearScreen();
    }

    cout << "-----------------------------------" << endl;
}

// Implementazione del metodo per verificare la vittoria di uno dei 2 Player
bool Player::checkWin(const Player *player) {
    // Iteriamo su ogni cella della board
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Se troviamo un 'O', la vittoria non è ancora stata raggiunta
            if (player->board[i][j] == 'O') {
                return false; 
            }
        }
    }
    // Se non abbiamo trovato alcun 'O', il giocatore ha vinto
    return true; 
}


// Implementazione del metodo per verificare se una nave e' affondata
string Player::isSank(Player *player, Player *enemy) const {

    // Per ogni singola nave
    for (int i = 0; i < 7; i++) {
        string nave = shiplist[i];
        char type = getChar(nave);
        bool isSunk = true;


        for (int row = 0; row < 10; row++) {
            for (int col = 0; col < 10; col++) {
                if (player->boardSunk[row][col] == type && player->board[row][col] != '@') {
                    isSunk = false;
                    break;
                }
            }
            if (!isSunk) break;
        }

        if (isSunk) {
            // Affondamento rilevato, aggiorna entrambe le mappe
            for (int row = 0; row < 10; row++) {
                for (int col = 0; col < 10; col++) {
                    if (player->boardSunk[row][col] == type) {
                        player->board[row][col] = '#';  // Segna la nave come affondata su board
                        enemy->boardMem[row][col] = '#';
                    }
                }
            }
            return nave; // Ritorna il nome della nave affondata
        }
    }

    return "error"; // Se nessuna nave e' stata affondata, ritorna "error"
}

// Funzione per sostituire un char con un altro char nella matrice di gioco
void replace(char board[10][10], const char replacedChar, const char newChar) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (board[i][j] == replacedChar) {
                board[i][j] = newChar;
            }
        }
    }
}

// Implementazione del metodo per la scelta della nave da posizionare
string Player::scegliNave(Player *player) {

  string nome;

  bool naveValida = false; // Flag per controllare se la nave e' valida

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

    int flag = 1 ;

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

                this->sottomarinox > 0)) {

      nome = "sottomarinox";

      naveValida = true;

    } else if (nome == "cacciatorpediniere" && this->cacciatorpediniere == 0 &&

               this->cacciatorpedinierex > 0) {

      nome = "cacciatorpedinierex";

      naveValida = true;

    } else if ((nome == "sottomarino" && this->sottomarino == 0 &&

                this->sottomarinox == 0) ||

               (nome == "cacciatorpediniere" && this->cacciatorpediniere == 0 &&

                this->cacciatorpedinierex == 0)) {

      cout << "Mi dispiace, capitano. Non abbiamo più " << nome

           << " a disposizione." << endl;

    } else { // Nave valida

      naveValida = true;

    }

  } while (!naveValida); // Continua a chiedere finché non viene inserita una nave valida

  // Aggiorna il numero di navi rimanenti solo se la nave e' valida

  if (nome == "portaerei") {

    this->portaerei--;

  } else if (nome == "corazzata") {

    this->corazzata--;

  } else if (nome == "incrociatore") {

    this->incrociatore--;

  } else if (nome == "sottomarino") {

    this->sottomarino--;

  } else if (nome == "sottomarinox") {

    this->sottomarinox--;

  } else if (nome == "cacciatorpediniere") {

    this->cacciatorpediniere--;

  } else if (nome == "cacciatorpedinierex") {

    this->cacciatorpedinierex--;

  }

  return nome;
  }

// Implementazione del metodo per gestire il piazzamento manuale delle na sulla board
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
                        cout << "Le coordinate inserite sono gia occupate da un'altra nave. Reinserisci le coordinate." << endl;
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
                        cout << "Le coordinate inserite sono gia' occupate da un'altra nave. Reinserisci le coordinate." << endl;
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

// Implementazione del metodo per gestire gli spari sulla board
char Player::strikeBoard(Player *player, Player *enemy) {
    int x, y;
    bool validCoords = false;

    while (!validCoords) {
        cout << "Capitano, inserisci le coordinate x (0-9) per lanciare il siluro: ";
        cin >> x;
        cout << "E ora le coordinate y (0-9), capitano: ";
        cin >> y;

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            validCoords = true;
        } else {
            cout << "Ehi capitano, quelle coordinate non sono valide! Riprova." << endl;
        }
    }

    if (enemy->board[x][y] == 'O') { // Caso 1: Il giocatore colpisce una nave
        enemy->board[x][y] = '@';
        player->boardMem[x][y] = '@';
        cout << "Bingo capitano! Hai colpito una nave nemica!" << endl;
        return '@';
    } else if (enemy->board[x][y] == '~') { // Caso 2: Il giocatore colpisce l'acqua
        enemy->board[x][y] = 'X';
        player->boardMem[x][y] = 'X';
        cout << "Ahah capitano, hai colpito solo acqua! Fortuna che non siamo sull'Oceano Atlantico!" << endl;
        return 'X';
    } else if (enemy->board[x][y] == '@') { // Caso 3: Il giocatore colpisce una porzione affondata di una nave
        cout << "Capitano, hai colpito una nave che era gia' affondata. Forse dovresti cambiare gli occhiali!" << endl;
        return 'X';
    } else { // Caso 4: Il giocatore colpisce una porzione di acqua gia' colpita
        cout << "Capitano, hai colpito lo stesso punto di prima! Forse e' ora di una pausa?" << endl;
        return 'X';
    }
}




////// FUNZIONI PER IL BOT //////

// Implementazione della funzione per la generazione di una coordinata casuale
int getRandCoords() {
  // Seed basato sul tempo corrente ad alta risoluzione
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed); // Mersenne Twister per una migliore casualita'
  std::uniform_int_distribution<int> distribution(0, 9);
  return distribution(generator);
}

// Implementazione della funziona per la generazione di una configurazione casuale
string getRandConfig() {
  // Seed basato sul tempo corrente ad alta risoluzione
  unsigned seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed); // Mersenne Twister per una migliore casualita'
  std::uniform_int_distribution<int> distribution(1, 2);
  int num = distribution(generator);
  return (num == 1) ? "verticale" : "orizzontale";
}

// Implementazione del metodo per il piazzamento automatico delle navi in tutte le board
void Player::autoPlacement(Player *player) {
    // Posizionamento automatico delle navi
  int x,y ;

    //  Posiziona ogni nave
  for (int i = 0; i < 7; ++i) {
    // Scelta della nave da posizionare
    string shiptype = shiplist[i];
    // Ottengo orientamento della nave
    string config = getRandConfig();

    char type = getChar(shiptype);
    bool validCoords = false;
    int lenght = shipSize(shiptype);

    while (!validCoords) {
        x = getRandCoords();
        y = getRandCoords();

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

                    }
                } else {

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

                    }
                } else {

                }
            }
        } else {

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
}

// implementazione dell'inizializzazione dei campi validCoords
void Player::initCoords (Player *player) {
    for (int i = 0 ; i < 10; i++) {
        for (int j = 0 ; j < 10; j++) {
            player->validCoords[i][j] = 0 ;
        }
    }
}

// Implemenazione dell'inizializzazione della simulazione di montecarlo
void Player::initSimulation(Player *player) {
    for (int i = 0 ; i < 10; i++) {
        for (int j = 0 ; j < 10; j++) {
            player->simBoard[i][j] = '~';
        }
    }
}

// Implemenazione della simulazione di montecarlo
void Player::montecarloSim(Player *player) {
    initSimulation(player);
    initCoords(player);
    // Loop principale della simulazione
    for (int i = 0 ; i < 1000 ; i++) {
        //Piazza le navi in modo pseudocasuale
        initSimulation(player);
        player->AIautoPlacement(player);
        // Calcolo delle coordinate migliori
        for (int j = 0 ; j < 10; j++) {
            for (int k = 0 ; k < 10 ; k++) {
                if (player->simBoard[j][k] == 'O') {
                    player->validCoords[j][k] += 1;
                }
            }
        }
    }
}

// Implementazione del metodo di selezione della migliore mossa
void Player::bestMove(Player *player, int &x, int &y) {
    int maxVal = -1;
    x = -1;
    y = -1;
    bool found = false;

    // Search for the best move
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Check if the AI has already shot at these coordinates
            if (player->boardMem[i][j] != '!') {
                // If the AI has not shot here and the value is greater than maxVal, update maxVal and the best coordinates
                if (player->validCoords[i][j] > maxVal) {
                    maxVal = player->validCoords[i][j];
                    x = i;
                    y = j;
                    found = true;
                }
            }
        }
    }

    // If a valid move was found, mark it as shot
    if (found) {
        player->validCoords[x][y] = -1; // Mark the cell as shot
    } else {
        player->huntMode = false; // Reset huntMode if no valid move was found
    }
}






// Implementazione del metodo di piazzamento pseudocasuale per le navi per la simulazione di montecarlo
void Player::AIautoPlacement(Player *player) {
  // PER TUTTE LE NAVI
  int x,y ;

  for (int i = 0; i < 7; ++i) {
    // Scelta della nave da posizionare
    string shiptype = shiplist[i];
    // Ottengo orientamento della nave
    string config = getRandConfig();

    char type = getChar(shiptype);
    bool validCoords = false;
    int lenght = shipSize(shiptype);

    while (!validCoords) {
        x = getRandCoords();
        y = getRandCoords();

        if (x >= 0 && x < 10 && y >= 0 && y < 10) {
            bool isOverlapping = false;
            if (config == "verticale") {
                if (x + lenght < 10) { // Controllo corretto per il limite verticale
                    for (int i = 0; i < lenght; i++) {
                        if (this->simBoard[x + i][y] != '~') {
                            isOverlapping = true;
                            break;
                        }
                    }
                    if (!isOverlapping) {
                        validCoords = true;
                    } else {

                    }
                } else {

                }
            } else if (config == "orizzontale") {
                if (y + lenght < 10) { // Controllo corretto per il limite orizzontale
                    for (int i = 0; i < lenght; i++) {
                        if (this->simBoard[x][y + i] != '~') {
                            isOverlapping = true;
                            break;
                        }
                    }
                    if (!isOverlapping) {
                        validCoords = true;
                    } else {

                    }
                } else {

                }
            }
        } else {

        }
    }

    // Piazzare la nave sulla griglia
    if (config == "orizzontale") {
        for (int i = 0; i < lenght; i++) {
            this->simBoard[x][y + i] = 'O'; // Posizionamento orizzontale corretto
        }
    } else if (config == "verticale") {
        for (int i = 0; i < lenght; i++) {
            this->simBoard[x + i][y] = 'O'; // Posizionamento verticale corretto
        }
    }
  }
}

// Implementazione del metodo StartGame per l'AI
void Player::AistartGame() {
    char answer;

    // Creazione dei giocatori
    Player player1(1, "Giocatore");
    Player player2(2, "AI");
    montecarloSim(&player2);

    // Chiedi all'utente se vuole posizionare le navi manualmente o automaticamente
    if (!AUTO_PLACEMENT) {
        cout << "Giocatore 1, vuoi posizionare le navi manualmente (M) o automaticamente (A)? ";
        cin >> answer;
        answer = tolower(answer);
    } else {
        answer = 'a'; // Imposta il posizionamento automatico se AUTO_PLACEMENT e' true
    }

    clearScreen();

    // Inizio del gioco
    if (answer == 'm') {
        cout << "Inizia il posizionamento delle navi per il Giocatore" << endl;
        for (int i = 0; i < 7; ++i) {
            string shipType = player1.scegliNave(&player1);
            player1.HandlePlacement(&player1, shipType);
            player1.stampa(player1.board);
        }
        clearScreen(); // Clear screen to prevent AI from seeing Player 1's board
        player2.autoPlacement(&player2);

    } else {
        // Posizionamento automatico delle navi
        player1.autoPlacement(&player1);
        player2.autoPlacement(&player2);
    }

    // Avvio del loop di gioco
    AigameLoop(&player1, &player2);
}

// Implementazione del loop di gioco per l'AI
void AigameLoop(Player *player1, Player *player2) {

    clearScreen();
    bool game_over = false;
    Player *human_player = player1;
    Player *ai_player = player2;

    while (!game_over) {
        // Turno del giocatore umano
        human_player->turno(human_player, ai_player);

        // Verifica se la partita e' finita dopo il turno del giocatore umano
        if (human_player->checkWin(ai_player)) {
            cout << "Partita finita! " << human_player->name << " ha vinto!" << endl;
            game_over = true;
            break;
        }

        // Conferma per il turno dell'IA (se CONFIRM_NEXT_TURN e' true)
        confirmAINextTurn();

        // Turno dell'AI
        ai_player->aiturno(ai_player, human_player);

        // Verifica se la partita e' finita dopo il turno dell'AI
        if (ai_player->checkWin(human_player)) {
            cout << "Partita finita! " << "I robot hanno dominato sugli umani" << endl;
            game_over = true;
        }
    }
}

// Implementazione del turno di gioco per l'AI
void Player::aiturno(Player *player, Player *enemy) {
    string sunkenOne = "";
    cout << "TURNO DELL'AI " << endl;

    bool keepTurn = true;

    while (keepTurn) {
        char result = player->AIstrikeBoard(player, enemy);
        sunkenOne = player->isSank(enemy, player);

        if (sunkenOne != "error") {
            char temp = getChar(sunkenOne);
            sunkenOne = getString(temp);
            cout << "MI SPIACE! L'AI ha affondato questa imbarcazione: " << sunkenOne << "!" << endl;
        }

        if (player->checkWin(enemy)) {
            cout << "Partita finita! I robot hanno dominato sugli umani" << endl;
            return;
        }

        if (CONTINUOUS_TURNS) {
            keepTurn = (result == '@');
        } else {
            keepTurn = false;
        }
    }

    player->updateMontecarloSim(player, enemy);
    cout << "Fine del turno dell'AI." << endl;
    confirmNextTurn();
    cout << "-----------------------------------" << endl;
}


// implementare il meotodo per gestire gli spari sulla board per l'AI
char Player::AIstrikeBoard(Player *player, Player *enemy) {
    int x, y;
    bool validShot = false;

    while (!validShot) {
        if (!player->huntMode) {
            bestMove(player, x, y);
        } else {
            vector<pair<int, int>> adjacentCells = getAdjacentSpiral(player->lastHitX, player->lastHitY, player);
            if (!adjacentCells.empty()) {
                // Seleziona una cella casuale dal vettore
                pair<int, int> selectedCell = adjacentCells[rand() % adjacentCells.size()];
                x = selectedCell.first;
                y = selectedCell.second;
            } else {
                // Se non ci sono celle adiacenti disponibili, scegli una cella casuale
                do {
                    x = getRandCoords();
                    y = getRandCoords();
                } while (player->boardMem[x][y] != '~');
            }
        }

        // Verifica se l'AI non ha ancora sparato in queste coordinate
        if (player->boardMem[x][y] == '~') {
            validShot = true;
        } else {
            // Se l'AI ha già sparato qui, deve scegliere un'altra cella
            player->huntMode = false;
        }
    }

    if (enemy->board[x][y] == 'O') {
        enemy->board[x][y] = '@';
        player->boardMem[x][y] = '!';
        player->validCoords[x][y] = -1;
        player->huntMode = true;
        player->lastHitX = x;
        player->lastHitY = y;
        cout << "Bingo! L'AI ha colpito una delle tue navi, umano!" << endl;
        return '@';
    } else if (enemy->board[x][y] == '~') {
        enemy->board[x][y] = 'X';
        player->boardMem[x][y] = '!';
        player->validCoords[x][y] = -1;
        cout << "Ahah, l'AI ha mancato il bersaglio! Forse dovresti insegnarle a mirare meglio!" << endl;
        return 'X';
    }

    // Valore di ritorno predefinito
    return '!';
}

vector<pair<int, int>> getAdjacentSpiral(int x, int y, Player *player) {
    vector<pair<int, int>> adjacentCells;

    // Define the spiral coordinates relative to (x, y)
    vector<pair<int, int>> spiralCoords = {
        {x, y+1}, {x-1, y}, {x, y-1}, {x+1, y}, {x-1, y+1}, {x+1, y+1}, {x-1, y-1}, {x+1, y-1},
        {x-2, y}, {x, y-2}, {x+2, y}, {x, y+2}, {x-2, y-1}, {x-1, y-2}, {x+1, y-2}, {x+2, y-1},
        {x-2, y+1}, {x+2, y+1}, {x-1, y+2}, {x+1, y+2}
    };

    // Check each coordinate in the spiral
    for (auto coord : spiralCoords) {
        int i = coord.first;
        int j = coord.second;

        // Check if the coordinates are within the board and the AI has not already shot there
        if (i >= 0 && i < 10 && j >= 0 && j < 10 && player->boardMem[i][j] != '!') {
            adjacentCells.push_back({i, j});
        }
    }

    return adjacentCells;
}

void Player::updateMontecarloSim(Player *player, Player *enemy) {
    // Resetta la simulazione
    initSimulation(player);
    initCoords(player);

    // Aggiorna la simulazione con le informazioni sulle celle colpite e mancate
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (enemy->board[i][j] == '@') {
                player->validCoords[i][j] = 100; // Cella colpita, assegna un valore elevato
            } else if (enemy->board[i][j] == 'X') {
                player->validCoords[i][j] = -1; // Cella mancata, assegna un valore negativo
            } else if (enemy->board[i][j] == '!' || player->boardMem[i][j] == '!') {
                player->validCoords[i][j] = -1; // Cella già colpita, assegna un valore negativo
            }
        }
    }

    // Esegui la simulazione di Montecarlo aggiornata
    for (int i = 0; i < 1000; i++) {
        initSimulation(player);
        player->AIautoPlacement(player);
        for (int j = 0; j < 10; j++) {
            for (int k = 0; k < 10; k++) {
                if (player->simBoard[j][k] == 'O' && player->validCoords[j][k] != -1) {
                    player->validCoords[j][k] += 1;
                }
            }
        }
    }
}


////// FUNZIONI DI STAMPA //////

// Implementazione della funzione per stampare la mappa principale (board)
void Player::stampaBoard() const {
  cout << "Mappa principale (board):\n";
  // Utilizzare un doppio ciclo per scorrere la board e stampare ogni casella
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

// Implementazione della funzione per stampare la mappa della memoria (boardMem)
void Player::stampaBoardMem() const {
  cout << "Mappa della memoria (boardMem):\n";
  // Utilizzare un doppio ciclo per scorrere la boardMem e stampare ogni casella
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      cout << boardMem[i][j] << " ";
    }
    cout << endl;
  }
}

// Implementazione della funzione per stampare la mappa delle navi affondate (boardSunk)
void Player::stampaBoardSunk() const {
  cout << "Mappa delle navi affondate (boardSunk):\n";
  // Utilizzare un doppio ciclo per scorrere la boardSunk e stampare ogni casella
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      cout << boardSunk[i][j] << " ";
    }
    cout << endl;
  }
}

// Implementazione della funzione per stampare la una mappa di gioco (M)
void Player::stampa(char M[10][10]) { // Aiuto del signor GPT in questa parte per lo stile
    clearScreen();
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
            cout << " "
                 << M[i][j];
        }
        cout << " |" << endl;
    }

    cout << "  ";
    for (int i = 0; i < 10; i++) {
        cout << "===";
    }
    cout << "===" << endl;
}

// Implementazione della funzione per stampare la mappa principale e della mappa dove si segnano i colpi (board & boardMem)
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