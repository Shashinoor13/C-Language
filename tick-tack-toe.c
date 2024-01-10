#include<stdio.h>

#define bool int
#define true 1
#define false 0

//This struct is used to store the player's name and symbol
//player 1 name is stored in players[0] and player 2 name is stored in players[1]
//player 1 symbol is stored in players[0] and player 2 symbol is stored in players[1]
typedef struct Player {
    char name[20];
    char symbol;
} Player;

//This struct is used to store the board and the players
//board is stored in board
//players are stored in players
typedef struct Ticktacktoe {
    char board[3][3];
    Player players[2];
} Ticktacktoe;

//This function is used to display the contents of the board inside the terminal
void printBoard(Ticktacktoe game){
    printf("Board:\n");
    for(int i = 0; i < 3; i++){
        printf("| %c | %c | %c |\n", game.board[i][0], game.board[i][1], game.board[i][2]);
        //This line prevents the line to be drawn after the last row
        if(i < 2){
            printf(" --- --- ---\n");
        }
    }
}

//This function is used to check if the move is valid
//A move is valid if the position is empty
bool checkValidMove(Ticktacktoe game, int x, int y){
    if(game.board[x][y] == ' '){
        return true;
    }
    return false;
}

//This is useful to check is the board is full
//The board is full if there is no empty space
bool isBoardFull(Ticktacktoe game){
   int counter = 0;
   //the board is 3*3
   int boardSize = 3*3;
    for(int i = 0; i < 3; i++){
         for(int j = 0; j < 3; j++){
              if(game.board[i][j] != ' '){
                counter++;
              }
         }
    }
    if(counter == boardSize){
        return true;
    }
    return false;
}

//This function is used to check if the game is over
//The game is over if there is a winner or the board is full
bool checkWinCondition(Ticktacktoe game,int playerTurnCounter){
    //if the total number of moves is less than 4, there cannot be a winner
    if (playerTurnCounter < 5)
    {
        return false;
    }
    
    //discard '' as a valid symbol
    char symbol = ' ';
    //check if there is a winner in the row
    for(int i = 0; i < 3; i++){
        if(game.board[i][0] != symbol && game.board[i][0] == game.board[i][1] && game.board[i][1] == game.board[i][2]){
            return true;
        }
    }
    //check if there is a winner in the column
    for(int i = 0; i < 3; i++){
        if(game.board[0][i] != symbol && game.board[0][i] == game.board[1][i] && game.board[1][i] == game.board[2][i]){
            return true;
        }
    }
    //check if there is a winner in the diagonal
    if(game.board[0][0] != symbol && game.board[0][0] == game.board[1][1] && game.board[1][1] == game.board[2][2]){
        return true;
    }
    if(game.board[0][2] != symbol && game.board[0][2] == game.board[1][1] && game.board[1][1] == game.board[2][0]){
        return true;
    }
    return false;

}

//This function is used to get the winner of the game
//The winner is the player who has 3 consecutive symbols in a row, column or diagonal
//This function is only called when checkWinCondition returns true
Player getWinner(Ticktacktoe game){
    Player winner;
    //discard '' as a valid symbol
    char symbol = ' ';
    //check if there is a winner in the row
    for(int i = 0; i < 3; i++){
        if(game.board[i][0] != symbol && game.board[i][0] == game.board[i][1] && game.board[i][1] == game.board[i][2]){
            winner = game.players[0];
            if(game.board[i][0] == game.players[1].symbol){
                winner = game.players[1];
            }
            return winner;
        }
    }
    //check if there is a winner in the column
    for(int i = 0; i < 3; i++){
        if(game.board[0][i] != symbol && game.board[0][i] == game.board[1][i] && game.board[1][i] == game.board[2][i]){
            winner = game.players[0];
            if(game.board[0][i] == game.players[1].symbol){
                winner = game.players[1];
            }
            return winner;
        }
    }
    //check if there is a winner in the diagonal
    if(game.board[0][0] != symbol && game.board[0][0] == game.board[1][1] && game.board[1][1] == game.board[2][2]){
        winner = game.players[0];
        if(game.board[0][0] == game.players[1].symbol){
            winner = game.players[1];
        }
        return winner;
    }
    if(game.board[0][2] != symbol && game.board[0][2] == game.board[1][1] && game.board[1][1] == game.board[2][0]){
        winner = game.players[0];
        if(game.board[0][2] == game.players[1].symbol){
            winner = game.players[1];
        }
        return winner;
    }
    return winner;
}

//This function is used to get the player who is currently playing
//playerTurnCounter is used to determine which player is playing
//playerTurnCounter can only be 0 or 1
Player getPlayerTurn(Ticktacktoe game, int playerTurnCounter){
    return game.players[playerTurnCounter % 2];
}

//This function is used to get the player name and symbol
//playerNumber is used to determine which player is being asked
//playerNumber can only be 1 or 2
//as nothing is being returned
//we can use pointers and pass game by reference to directly manipulate the
//game data structure
void getPlayerInformation(Ticktacktoe *game, int playerNumber){
    printf("Player %d\n", playerNumber);
    printf("Enter player %d name: ", playerNumber);
    scanf("%s", game->players[playerNumber - 1].name);
    printf("Enter player %d symbol: ", playerNumber);
    scanf(" %c", &game->players[playerNumber - 1].symbol);
}

//This function is used to initialize the game board
//The game board is initialized to be empty
void initializeGameBoard(Ticktacktoe *game){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            game->board[i][j] = ' ';
        }
    }
}

int main(){
    Ticktacktoe game;
    int playerTurnCounter = 0;
    getPlayerInformation(&game, 1);
    getPlayerInformation(&game, 2);

    printf("Player 1 name: %s\n", game.players[0].name);
    printf("Player 1 symbol: %c\n", game.players[0].symbol);
    printf("Player 2 name: %s\n", game.players[1].name);
    printf("Player 2 symbol: %c\n", game.players[1].symbol);

    initializeGameBoard(&game);
    printBoard(game);
    while(true){
        Player currentPlayer = getPlayerTurn(game, playerTurnCounter);
        printf("Player %s turn\n", currentPlayer.name);
        printf("Enter x: ");
        int x;
        int xCheck  = scanf("%d", &x);
        if(xCheck != 1){
            printf("Invalid input\n");
            break;
        }
        printf("Enter y: ");
        int y;
        int yCheck = scanf("%d", &y);
        if(yCheck != 1){
            printf("Invalid input\n");
            break;
        }
        if(x < 0 || x > 2 || y < 0 || y > 2){
            printf("Out of Bounds\n");
            continue;
        }
        if(checkValidMove(game, x, y)){
            game.board[x][y] = currentPlayer.symbol;
            printBoard(game);
            if(checkWinCondition(game,playerTurnCounter)){
                Player winner = getWinner(game);
                printf("%s WON THE GAME", winner.name);
                break;
            }
            if(isBoardFull(game)){
                printf("Game over\n");
                break;
            }
            playerTurnCounter++;
        }else{
            printf("Invalid move\n");
        }
    }
    return 0;
}