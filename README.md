# Terminal memory game

This is a simple project to play a memory in the terminal.
    
## Installation

If you want to play, clone this repository and compile it using make command
```shell
git clone https://github.com/Angel-Karasu/terminal-memory-game.git;
cd terminal-memory-game;
make all;
./memory;
```

## How to Play

1. Run the executable file : `memory`
2. Prepare the game :
  - Choose the number of players, must be higher than 1
  - Choose the number of rows, must be between 1 and number of cards / 2
  - Choose the number of columns, must be between 1 and number of cards / number of rows
3. Player's turn :
  - Select the first card that you want to see with its position, (i,j)
  - Select the second card that you want to see with its position, (i,j)
  - If it's the same cards, you win 1 point and you can play again else it's the next player's turn
4. End game :
  - The player with the most points wins
  - Choose if you want to play again
  
## License

This project is licensed under the [GNU GPLv3](https://choosealicense.com/licenses/gpl-3.0/).

See the `LICENSE` file for details.
