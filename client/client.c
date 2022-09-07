#include <stdio.h>
#include <stdlib.h>

char gameBanner[] = " .d8888b.  888           ___  _ _  | |(_) _ _   ___  \nd88P  Y88b 888       _  / _ \\| ' \\ | || || ' \\ / -_) \n888    888 888      |_| \\___/|_||_||_||_||_||_|\\___| \n888        88888b.   .d88b.  .d8888b  .d8888b        \n888        888 \"88b d8P  Y8b 88K      88K            \n888    888 888  888 88888888 \"Y8888b. \"Y8888b.       \nY88b  d88P 888  888 Y8b.          X88      X88       \n \"Y8888P\"  888  888  \"Y8888   88888P'  88888P'       \n";


char mainBoard[7][7];

void movePieces(char startY, int startX, char destinationY, int destinationX){
	int finalStartX, finalDestinationX;

	char pieceType = mainBoard[startY][startX];

	switch(startX){
		case 'a':
			finalStartX = 1;
			break;
		case 'b':
			finalStartX = 2;
			break;
		case 'c':
			finalStartX = 3;
			break;
		case 'd':
			finalStartX = 4;
			break;
		case 'e':
			finalStartX = 5;
			break;
		case 'f':
			finalStartX = 6;
			break;
		case 'g':
			finalStartX = 7;
			break;
		case 'h':
			finalStartX = 8;
			break;
		default:
			printf("error: invalid value X in function movePieces");
	}

	switch(destinationX){
		case 'a':
			finalDestinationX = 1;
			break;
		case 'b':
			finalDestinationX = 2;
			break;
		case 'c':
			finalDestinationX = 3;
			break;
		case 'd':
			finalDestinationX = 4;
			break;
		case 'e':
			finalDestinationX = 5;
			break;
		case 'f':
			finalDestinationX = 6;
			break;
		case 'g':
			finalDestinationX = 7;
			break;
		case 'h':
			finalDestinationX = 8;
			break;
		default:
			printf("error: invalid value X in function movePieces");
	}

	mainBoard[startY][finalStartX] = ' ';
	
	mainBoard[destinationY][finalDestinationX] = pieceType;

}

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
				// casella vuota
				mainBoard[y][x] = ' ';
			}
		}
	}
	return;
}

// orientation:
// 1 - normal
// 2 - reverse
void printBoard(char board[7][7], int orientation, int refresh){
	if(refresh == 1){
		system("clear");
	}
	
	int gameY, gameX, Nline;

	switch(orientation){
		case 1:
			for(gameY = 0; gameY <= 7; gameY++){
				printf("\n   +---+---+---+---+---+---+---+---+\n %d ", abs(gameY - 8));
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
			break;
		case 2:
			for(gameY = 7; gameY >= 0; gameY--){
				printf("\n   +---+---+---+---+---+---+---+---+ \n %d ", abs(8 - gameY));
				for(gameX = 7; gameX >= 0; gameX--){
					printf("| %c ", board[gameY][gameX]);
					if(gameX == 0){
						printf("|");
					}
				}
				if(gameY == 0){
					printf("\n   +---+---+---+---+---+---+---+---+  \n");
					printf("     h   g   f   e   d   c   b   a  \n\n");
				}
			}
			break;
		default:
			printf("error: wrong input in function printBoard()");
	}
}

void startGame(){
	int gameFinish = 0;

	// must change in online version
	boardCreate();

	while(gameFinish == 0){
		system("clear");

		char moveInput[6];
		char startValueY, destinationValueY;
		int startValueX, destinationValueX;

		printf("%s", gameBanner);
		printf("\n\n game started:\n\n");

		printBoard(mainBoard, 1, 1);
		
		// take move input
		printf("your move: ");
		scanf("%s", &moveInput);
		
		// typical string: "2:h-5:f"
		startValueX = (int)(moveInput[2]);
		destinationValueX = (int)(moveInput[6]);
		
		movePieces(moveInput[2], startValueX, moveInput[6], destinationValueX);
		printBoard(mainBoard, 1, 1);
	}
}

void quit(){
	printf("bye!\n");
	exit(1);
}

int main(){
	system("clear");

	// menu
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
