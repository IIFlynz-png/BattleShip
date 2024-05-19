#include <iostream>
#include "game_engine.h" // Assicurati di includere il file header corretto
#include <chrono>

int main() {
    int choice;

    do {
        clearScreen();
        displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                displayRules();
            break;
            case 2: {
                Player player;
                player.startGame();
                break;
            }
            case 3:
                displaySettings();
            break;
            case 4:
                cout << "Arrivederci!" << endl;
            break;
            default:
                cout << "Opzione non valida. Riprova." << endl;
            break;
        }
    } while (choice != 4);

    return 0;
}
