#include <stdio.h>
#include <stdlib.h>

char gameBanner[] = " .d8888b.  888           ___  _ _  | |(_) _ _   ___  \nd88P  Y88b 888       _  / _ \\| ' \\ | || || ' \\ / -_) \n888    888 888      |_| \\___/|_||_||_||_||_||_|\\___| \n888        88888b.   .d88b.  .d8888b  .d8888b        \n888        888 \"88b d8P  Y8b 88K      88K            \n888    888 888  888 88888888 \"Y8888b. \"Y8888b.       \nY88b  d88P 888  888 Y8b.          X88      X88       \n \"Y8888P\"  888  888  \"Y8888   88888P'  88888P'       \n";


char mainBoard[7][7];

void quit(){
	printf("bye!\n");
	exit(1);
}

// variable for the funcion below
int returnValue = 10;
int XcoordinatesConverter(char coordinateX){
	if(coordinateX == 'a'){
		returnValue = 0;
	} else if(coordinateX == 'b'){
		returnValue = 1;
	} else if(coordinateX == 'c'){
		returnValue = 2;
	} else if(coordinateX == 'd'){
		returnValue = 3;
	} else if(coordinateX == 'e'){
		returnValue = 4;
	} else if(coordinateX == 'f'){
		returnValue = 5;
	} else if(coordinateX == 'g'){
		returnValue = 6;
	} else if(coordinateX == 'h'){
		returnValue = 7;
	}

	return returnValue;
}

int ceckMove(char board[7][7], int startY, char startX, int destinationY, char destinationX, char pieceType){
	// setup the rules
	// p can move 1 each time only forward, and must it in diagonal
	if(pieceType == 'p'){
		int distance = startY - destinationY;
		if(distance == 1){
			return 1;
		} else if(distance == 2){
			if(startY == 2 || startY == 7){
				return 1;
			}
		} else {
			return 2;
		}
	}
	// t (tower) can move only on the y or x asxis
	if(pieceType == 't'){
		return 3;
	}
	// c (horse) can do "l" move in all orientation
	if(pieceType == 'c'){
		return 3;
	}
	// a (alfier) can move diagonaly
	if(pieceType == 'a'){
		return 3;
	}
	// f (fenale) can move were she wants
	if(pieceType == 'f'){
		return 3;
	}
	// m (male) can move once in all direction;
	if(pieceType == 'm'){
		return 3;
	}

	return 0;
}

int movePieces(char board[7][7], int startY, char startX, int destinationY, char destinationX){
	startY = abs(startY - 7);
	destinationY = abs(destinationY - 7);

	int finalStartX, finalDestinationX;

	finalStartX = XcoordinatesConverter(startX);
	finalDestinationX = XcoordinatesConverter(destinationX);

	char pieceType = board[startY][finalStartX];

	int moveValidation = ceckMove(mainBoard, startY, finalStartX, destinationY, finalDestinationX, pieceType);

	// if the move is legit
	if(moveValidation == 1){
		board[startY][finalStartX] = '\x20';
		board[destinationY][finalDestinationX] = pieceType;
	}

	return moveValidation;
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
void printBoard(char board[7][7], int orientation, int moveReturnMessage){
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

					if(moveReturnMessage == 0){
						printf("Error 0: bad movePieces() or ceckMove() functioning\n");
					} else if(moveReturnMessage == 1){
						printf("\n");
					} else if(moveReturnMessage == 2){
						printf("Error 2: illegal move");
					} else if(moveReturnMessage == 3){
						printf("Error 3: siuuuum");
					}
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
					}epi
				}
				if(gameY == 0){
					printf("\n   +---+---+---+---+---+---+---+---+  \n");
					printf("     h   g   f   e   d   c   b   a  \n\n");

					if(moveReturnMessage == 0){
						printf("Error 0: bad movePieces() or ceckMove() functioning\n");
					} else if(moveReturnMessage == 1){
						printf("\n");
					} else if(moveReturnMessage == 2){
						printf("Error 2: illegal move");
					} else if(moveReturnMessage == 3){
						printf("Error 3: siuuuum");
					}
				}
			}
			break;
		default:
			printf("error: wrong input in function printBoard()");
	}
}

void startGame(char gameOrientation[]){
	int movePiecesReturn = 0;
	int gameFinish = 0;
	int boardOrientation = 1;

	if(gameOrientation == "normal"){
		boardOrientation = 1;
	} else if(gameOrientation == "reverse"){
		boardOrientation = 2;
	}

	// must change in online version
	boardCreate();

	while(gameFinish == 0){
		system("clear");

		int startValueY, destinationValueY;
		char moveInput[6];

		printf("%s", gameBanner);

		printBoard(mainBoard, boardOrientation, movePiecesReturn);

		// take move input
		printf("your move: ");
		scanf("%s", &moveInput);

		if(moveInput == "qt"){
			quit();
		} else if (moveInput == "rs"){
			startGame(gameOrientation);
		}

		// typical string: "2:h-5:f"
		startValueY = atoi(&moveInput[0]);
		destinationValueY = atoi(&moveInput[4]);

		int movePiecesReturn = movePieces(mainBoard, startValueY-1, moveInput[2], destinationValueY-1, moveInput[6]);
	}
}

void menu(){
	system("clear");

	char clientOrientation[] = "normal";

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
			startGame(clientOrientation);
			break;
		case 2:
			quit();
			break;
		default:
			printf("invalid value");
	}
}

int main(){
	menu();
}
