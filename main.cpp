#include <iostream>
#include "game_engine.h" // Assicurati di includere il file header corretto
#include <chrono>

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
    cout << "2. Gioca" << endl;
    cout << "3. Esci" << endl;
    cout << "------------------------------------" << endl;
    cout << "Seleziona un'opzione: ";
}

void displayRules() {
    cout << "Regole del gioco:" << endl;
    cout << "- Ogni giocatore ha una flotta di 7 navi:" << endl;
    cout << "  1 Portaerei (5 celle) - 'P'" << endl;
    cout << "  1 Corazzata (4 celle) - 'C'" << endl;
    cout << "  1 Incrociatore (3 celle) - 'I'" << endl;
    cout << "  1 Cacciatorpediniere (3 celle) - 'D'" << endl;
    cout << "  1 Cacciatorpedinierex (3 celle) - 'N'" << endl;
    cout << "  1 Sottomarino (2 celle) - 'S'" << endl;
    cout << "  1 Sottomarinox (2 celle) - 'R'" << endl;
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

int main() {
    int choice;

    do {
        clearScreen();
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                displayRules();
                break;
            }
            case 2: {
                Player player;
                player.startGame();
                break;
            }
            case 3:
                cout << "Arrivederci!" << endl;
                break;
            default:
                cout << "Opzione non valida. Riprova." << endl;
                break;
        }
    } while (choice != 3);

    return 0;
}
