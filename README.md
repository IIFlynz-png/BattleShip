# BattleShip

Questo progetto è un gioco di Battaglia Navale sviluppato in C++. Il gioco supporta sia la modalità giocatore contro giocatore che la modalità giocatore contro intelligenza artificiale.

## Caratteristiche

- Modalità giocatore contro giocatore.
- Modalità giocatore contro intelligenza artificiale.
- L'intelligenza artificiale utilizza una simulazione di Monte Carlo per determinare le mosse migliori.
- Possibilità di posizionare le navi manualmente o automaticamente.
- Visualizzazione della griglia di gioco e dello stato delle navi.

## Installazione

Per eseguire il gioco, è necessario avere un compilatore C++ installato sul proprio sistema. Puoi scaricare il codice sorgente del progetto clonando la repository GitHub.

```bash
git clone https://github.com/IIFlynz-png/BattleShip
```

Dopo aver clonato la repository, naviga nella directory del progetto e compila il codice utilizzando il tuo compilatore C++.

```bash
cd directory
g++ -o game main.cpp game_engine.cpp
```

Infine, esegui il gioco con il seguente comando:

```bash
./game
```

## Utilizzo

Dopo aver avviato il gioco, verrà visualizzato un menu con diverse opzioni. Puoi scegliere di giocare una partita, visualizzare le regole del gioco o modificare le impostazioni.

Durante una partita, ti verrà chiesto di inserire le coordinate per sparare alle navi avversarie. Se colpisci una nave, avrai un altro turno. Il gioco continua fino a quando tutte le navi di un giocatore sono state affondate.


# Breve spiegazione sulla struttura del gioco

Il progetto è un gioco di Battaglia Navale sviluppato in C++. Il gioco supporta sia la modalità giocatore contro giocatore che la modalità giocatore contro intelligenza artificiale.

## Struttura del Codice

Il codice è diviso principalmente in due file: `game_engine.h` e `game_engine.cpp`.

### `game_engine.h`

Questo file contiene la dichiarazione della classe `Player` e delle sue funzioni membro. La classe `Player` rappresenta un giocatore nel gioco di Battaglia Navale. Ogni giocatore ha una griglia di gioco, una memoria di bordo e una griglia di navi affondate. Inoltre, ogni giocatore ha un insieme di navi che può posizionare sulla griglia di gioco.

Le funzioni membro della classe `Player` includono funzioni per inizializzare la griglia di gioco, posizionare le navi, sparare alla griglia dell'avversario, controllare se una nave è affondata, controllare se un giocatore ha vinto e gestire il turno di un giocatore.

### `game_engine.cpp`

Questo file contiene l'implementazione delle funzioni membro della classe `Player` dichiarate in `game_engine.h`. Inoltre, contiene l'implementazione di alcune funzioni globali utilizzate nel gioco, come la funzione per visualizzare il menu del gioco e la funzione per avviare il loop di gioco.

## Funzioni Principali

- `startGame()`: Questa funzione avvia una partita tra due giocatori umani. Chiede ai giocatori di posizionare le loro navi sulla griglia di gioco e poi avvia il loop di gioco.

- `AistartGame()`: Questa funzione avvia una partita tra un giocatore umano e l'intelligenza artificiale. Chiede al giocatore umano di posizionare le sue navi sulla griglia di gioco, posiziona automaticamente le navi dell'IA sulla griglia di gioco e poi avvia il loop di gioco.

- `turno(Player *player, Player *enemy)`: Questa funzione gestisce il turno di un giocatore. Chiede al giocatore di scegliere le coordinate per sparare alla griglia dell'avversario e aggiorna la griglia di gioco in base al risultato dello sparo.

- `aiturno(Player *player, Player *enemy)`: Questa funzione gestisce il turno dell'IA. L'IA sceglie le coordinate per sparare alla griglia dell'avversario e aggiorna la griglia di gioco in base al risultato dello sparo.

- `checkWin(const Player *player)`: Questa funzione controlla se un giocatore ha vinto la partita. Un giocatore vince la partita se tutte le navi dell'avversario sono state affondate.

## Intelligenza Artificiale

L'intelligenza artificiale nel gioco utilizza una simulazione di Monte Carlo per determinare le mosse migliori. Durante il suo turno, l'IA può scegliere di sparare a una cella adiacente a una cella in cui ha colpito una nave nel turno precedente (modalità di caccia) o può scegliere di sparare a una cella basata sulla simulazione di Monte Carlo (modalità di esplorazione).

## Contribuire

Le contribuzioni sono le benvenute! Per contribuire al progetto:

Scrivere a:
cavallinipavel097@gmail.com
