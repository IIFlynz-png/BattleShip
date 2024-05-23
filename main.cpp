#include <iostream>
#include "game_engine.h"



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
            case 3: {
                Player player;
                player.AistartGame();
                break;
                
            }
            case 4:
                displaySettings();
            break;
            case 5:
                cout << "Arrivederci!" << endl;
            break;
            default:
                cout << "Opzione non valida. Riprova." << endl;
            break;
        }
    } while (choice != 5);

    return 0;
}