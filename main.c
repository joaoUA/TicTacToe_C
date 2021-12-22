#include <stdio.h>
#include <stdlib.h>

#define BOARD_WIDTH 3
#define BOARD_HEIGHT 3

typedef struct PlayerCoordinates
{
    int x;
    int y;
    int player;
} Player;

void drawBoard(int board[BOARD_HEIGHT][BOARD_WIDTH]);
char getSymbol(int player);
int getPlayerInput();
void mapPlayToBoard(int play, Player *coords);
void submitPlayerInput(int board[BOARD_HEIGHT][BOARD_WIDTH], Player coords);
void switchPlayer(Player *coords);
int checkForWinCondition(int board[BOARD_HEIGHT][BOARD_WIDTH], Player coords);

int main()
{
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    int gameState = -1;
    int numberOfPlays = 0;
    int play = -1;
    Player coords;
    coords.player = 0;

    do
    {
        drawBoard(board);

        play = getPlayerInput();
        mapPlayToBoard(play, &coords);
        submitPlayerInput(board, coords);
        numberOfPlays++;

        gameState = checkForWinCondition(board, coords);

        if(gameState == -1 && numberOfPlays == 9) gameState = 2;

        if(gameState == -1) switchPlayer(&coords);
        system("cls");
    }
    while(gameState == -1);


    drawBoard(board);
    switch(gameState)
    {
        case 0:
        case 1:
            printf("Congrats to player %d !", coords.player+1);
            break;
        case 2:
            printf("Draw! No more plays available.");
    }

    return 0;
}

void drawBoard(int board[BOARD_HEIGHT][BOARD_WIDTH])
{
    for(int i = 0; i < BOARD_HEIGHT; i++)
    {
        printf("|");
        for(int j = 0; j < BOARD_WIDTH; j++)
        {
            printf("%c|", getSymbol(board[i][j]) );
        }
        printf("\n");
    }
}

char getSymbol(int player)
{
    switch(player)
    {
        case 0:
            return 'X';
        case 1:
            return 'O';
        default:
            return ' ';
    }
}

int getPlayerInput()
{
    int input = 0;
    ///Input Validation
    do
    {
        scanf("%d", &input);
    }
    while(input < 1 || input > 9);

    return input;
}

void mapPlayToBoard(int play, Player *coords)
{

    switch(play)
    {
        case 1:
            coords->x = 2;
            coords->y = 0;
            break;
        case 2:
            coords->x = 2;
            coords->y = 1;
            break;
        case 3:
            coords->x = 2;
            coords->y = 2;
            break;
        case 4:
            coords->x = 1;
            coords->y = 0;
            break;
        case 5:
            coords->x = 1;
            coords->y = 1;
            break;
        case 6:
            coords->x = 1;
            coords->y = 2;
            break;
        case 7:
            coords->x = 0;
            coords->y = 0;
            break;
        case 8:
            coords->x = 0;
            coords->y = 1;
            break;
        case 9:
            coords->x = 0;
            coords->y = 2;
            break;
    }
}

void submitPlayerInput(int board[BOARD_HEIGHT][BOARD_WIDTH], Player coords)
{
    board[coords.x][coords.y] = coords.player;
    printf("%d\n", board[coords.x][coords.y]);
    return;
}

void switchPlayer(Player *coords)
{
    if((coords->player) == 0) coords->player = 1;
    else (coords->player) = 0;
    return;
}

int checkForWinCondition(int board[BOARD_HEIGHT][BOARD_WIDTH], Player coords)
{
    ///return 0 for player1 win, 1 for player2
    int state = coords.player;
    int counter = 0;

    ///Check Vertical Win
    for(int i = 0; i < BOARD_HEIGHT; i++) counter += board[i][coords.y];
    if(counter == BOARD_HEIGHT * coords.player) return state;
    else counter = 0;

    ///Check Horizontal Win
    for(int i = 0; i < BOARD_WIDTH; i++) counter += board[coords.x][i];
    if(counter == BOARD_WIDTH * coords.player) return state;
    else counter = 0;

    ///Check Horizontal (TopLeft to BottomRight)
    for(int i = 0; i < BOARD_HEIGHT; i++) counter += board[i][i];
    if(counter == BOARD_HEIGHT * coords.player) return state;
    else counter = 0;

    ///Check Horizontal (TopRight to BottomLeft)
    for(int i = 0; i < BOARD_HEIGHT; i++) counter += board[BOARD_WIDTH - 1 - i][i];
    if(counter == BOARD_HEIGHT * coords.player) return state;
    else counter = 0;

    return -1;

}

