#include <stdio.h>
#include <stdlib.h>

char gameBanner[] = " .d8888b.  888           ___  _ _  | |(_) _ _   ___  \nd88P  Y88b 888       _  / _ \\| ' \\ | || || ' \\ / -_) \n888    888 888      |_| \\___/|_||_||_||_||_||_|\\___| \n888        88888b.   .d88b.  .d8888b  .d8888b        \n888        888 \"88b d8P  Y8b 88K      88K            \n888    888 888  888 88888888 \"Y8888b. \"Y8888b.       \nY88b  d88P 888  888 Y8b.          X88      X88       \n \"Y8888P\"  888  888  \"Y8888   88888P'  88888P'       \n";


char mainBoard[7][7];

void boardCreate(){
	int y, x;
	for(y = 0; y <= 7; y++){
		for(x = 0; x <= 7; x++){
			if(y == 1 || y == 6){
				// pedone
				mainBoard[y][x] = 'p';
			} else if(y == 0 || y == 7){
				if(x == 0 || x == 7){
					// torre
					mainBoard[y][x] = 't';
				}
				if(x == 1 || x == 6){
					// cavallo
					mainBoard[y][x] = 'c';
				}
				if(x == 2 || x == 5){
					// alfiere
					mainBoard[y][x] = 'a';
				}
				if(x == 3){
					// regina
					mainBoard[y][x] = 'f';
				}
				if(x == 4){
					// re
					mainBoard[y][x] = 'm';
				}
			} else if(y >= 2 && y <= 5){
				mainBoard[y][x] = ' ';
			}
		}
	}
	return;
}

void printBoard(char board[7][7]){
	int gameY, gameX, Nline;

	for(gameY = 0; gameY <= 7; gameY++){
		Nline = gameY + 1;
		printf("\n   +---+---+---+---+---+---+---+---+\n %d ",Nline++);
		for(gameX = 0; gameX < 8; gameX++){
			printf("| %c ", board[gameY][gameX]);
			if(gameX == 7){
				printf("|");
			}
		}
		if(gameY == 7){
			printf("\n   +---+---+---+---+---+---+---+---+  \n");
			printf("     a   b   c   d   e   f   g   h  \n\n");
		}
	}
}

void startGame(){
	system("clear");

	printf("%s", gameBanner);
	printf("\n\n game started:\n\n");

	boardCreate();
	printBoard(mainBoard);
}

void quit(){
	printf("\nbye! \n");
	exit(1);
}

int main(){
	system("clear");

	printf("%s", gameBanner);

	int inputChoise;

	printf("\n");
	printf("1: start a game \n");
	printf("2: quit \n");
	printf("> ");

	scanf("%d", &inputChoise);

	switch(inputChoise){
		case 1:
			startGame();
			break;
		case 2:
			quit();
			break;
		default:
			printf("invalid value");
	}

	return 0;
}
