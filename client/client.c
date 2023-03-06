#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char gameBanner[] = " .d8888b.  888           ___  _ _  | |(_) _ _   ___  \nd88P  Y88b 888       _  / _ \\| ' \\ | || || ' \\ / -_) \n888    888 888      |_| \\___/|_||_||_||_||_||_|\\___| \n888        88888b.   .d88b.  .d8888b  .d8888b        \n888        888 \"88b d8P  Y8b 88K      88K            \n888    888 888  888 88888888 \"Y8888b. \"Y8888b.       \nY88b  d88P 888  888 Y8b.          X88      X88       \n \"Y8888P\"  888  888  \"Y8888   88888P'  88888P'       \n";

char mainBoard[8][8];

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

/*
return:
 0 - err: unknown piece
 1 - ok: random good phrase
 2 - eated: eate: eated
 3 - err: illegal move
*/
int ceckMove(char board[8][8], int startY, int startX, int destinationY, int destinationX, char pieceType){
	int deltaDistanceY = startY - destinationY;
	int deltaDistanceX = startX - destinationX;
	// setup the rules
	switch(pieceType){
		// p (pown) can move 1 each time only forward, and must it in diagonal
		case 'p':
			if((deltaDistanceX == 0 && deltaDistanceY == 1 && mainBoard[destinationY][destinationX] == '\x20') || (deltaDistanceY == 2 && (startY == 1 || startY == 6))){
				return 1;
			} else if(abs(deltaDistanceX) == 1 && deltaDistanceY == 1 && mainBoard[destinationY][destinationX] != '\x20'){
				return 2;
			} else {
				return 3;
			}
			break;

		// t (tower) can move only on the y or x asxis
		case 't':
			if(deltaDistanceX == 0 && deltaDistanceY != 0){
				for(int i = 0; i < deltaDistanceY-1; i++){
					if(mainBoard[startY + i][destinationX] != '\x20'){
						return 3;
					}
				}
				if(mainBoard[destinationY][destinationX] == '\x20'){
					return 1;
				} else {
					return 2;
				}
			} else if(deltaDistanceY == 0 && deltaDistanceX != 0){
				for(int i = 0; i < deltaDistanceX; i++){
					if(mainBoard[destinationY][startX + i] != '\x20'){
						return 3;
					}
				}
				if(mainBoard[destinationY][destinationX] == '\x20'){
					return 1;
				} else {
					return 2;
				}
			} else {
				return 3;
			}
			break;

		// h (horse) can do "l" move in all orientation
		case 'h':
			if((abs(deltaDistanceX) == 2 && abs(deltaDistanceY) == 1) || (abs(deltaDistanceX) == 1 && abs(deltaDistanceY) == 2)){
				if(mainBoard[destinationY][destinationX] == '\x20'){
					return 1;
				} else {
					return 2;
				}
			} else {
				return 3;
			}
			break;
	
		// b (bishop) can move diagonaly
		case 'b':
			if(abs(deltaDistanceX) == abs(deltaDistanceY)){
				for(int i = 0; i < deltaDistanceX-1; i++){
					if(mainBoard[startY + i][startX + i] != '\x20'){
						return 3;
					}
				}
				if(mainBoard[destinationY][destinationX] != '\x20'){
					return 2;
				} else {
					return 1;
				}
			} else {
				return 3;
			}
			break;

		// q (queen) can move were she wants
		case 'q':
			return 1;

		// k (king) can move once in all direction;
		case 'k':
			if(abs(deltaDistanceX) == 1 || abs(deltaDistanceY) == 1){
				if(mainBoard[destinationY][destinationX] == '\x20'){
					return 1;
				} else {
					return 2;
				}
			} else {
				return 3;
			}

		default:
			return 0;
	}
}

int movePieces(char board[8][8], int startY, char startX, int destinationY, char destinationX){
	startY = abs(startY - 7);
	destinationY = abs(destinationY - 7);

	int finalStartX, finalDestinationX;

	finalStartX = XcoordinatesConverter(startX);
	finalDestinationX = XcoordinatesConverter(destinationX);

	char pieceType = board[startY][finalStartX];

	int moveValidation = ceckMove(mainBoard, startY, finalStartX, destinationY, finalDestinationX, pieceType);

	// if the move is legit
	if(moveValidation == 1 || moveValidation == 2){
		board[startY][finalStartX] = '\x20';
		board[destinationY][finalDestinationX] = pieceType;
	}
	return moveValidation;
}

void boardCreate(){
	for(int y = 0; y < 8; y++){
		for(int x = 0; x < 8; x++){
			if(y == 0 || y == 7){
				if(x == 0 || x == 7){
					mainBoard[y][x] = 't';
				} else if(x == 1 || x == 6){
					mainBoard[y][x] = 'h';
				} else if(x == 2 || x == 5){
					mainBoard[y][x] = 'b';
				} else if(x == 3){
					mainBoard[y][x] = 'q';
				} else if(x == 4){
					mainBoard[y][x] = 'k';
				}	
			} else if(y == 1 || y == 6){
				mainBoard[y][x] = 'p';
			} else {
				mainBoard[y][x] = ' ';
			}
		}
		printf("\n");
	}
	return;
}

// number of prints (so number of move)
int move = 0;
// orientation:
// 1 - normal
// 2 - reverse
void printBoard(char board[8][8], int orientation, int moveReturnMessage){
	int gameY, gameX, Nline;
	char background[] = "\e[49m";
	char defaultBackground[] = "\e[49m";
	char foreground[] = "\e[39m";

	switch(orientation){
		case 1:
			for(gameY = 0; gameY < 8; gameY++){
				printf("\n   +---+---+---+---+---+---+---+---+\n %d ", abs(gameY - 8));
				for(gameX = 0; gameX < 8; gameX++){
					/*
					if(gameY % 2 == 0){
						if(gameX % 2 == 0){
							strcpy(background, "\e[47m"); //light grey
						} else {
							strcpy(background, "\e[43m"); //dark yellow
						}
					} else {
						if(gameX % 2 == 0){
							strcpy(background, "\e[43m"); //dark yellow
						} else {
							strcpy(background, "\e[47m"); //light grey
						}
					}
					*/
					printf("|%s%s %c %s", foreground, background, board[gameY][gameX], defaultBackground);
					if(gameX == 7){
						printf("|");
					}
				}
				if(gameY == 7){
					printf("\n   +---+---+---+---+---+---+---+---+  \n");
					printf("     a   b   c   d   e   f   g   h  \n\n");

					if(move == 0){
						printf("Make your first move!\n");
					} else {
						if(moveReturnMessage == 0){
							printf("Error: unknown piece :(\n");
						} else if(moveReturnMessage == 1){
							// random phrase
							printf("Nice move!\n");
						} else if(moveReturnMessage == 2){
							// random eated phrase
							printf("Eated!\n");
						} else if(moveReturnMessage == 3){
							printf("Error: illegal move :(\n");
						} else if(moveReturnMessage == 4){
							printf("Bye!");
						}
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
					}
				}
				if(gameY == 0){
					printf("\n   +---+---+---+---+---+---+---+---+  \n");
					printf("     h   g   f   e   d   c   b   a  \n\n");

					if(move == 0){
						printf("Make your first move!\n");
					} else {
						if(moveReturnMessage == 0){
							printf("Error: unknown piece :(\n");
						} else if(moveReturnMessage == 1){
							// random phrase
							printf("Nice move!\n");
						} else if(moveReturnMessage == 2){
							// random eated phrase
							printf("Eated!\n");
						} else if(moveReturnMessage == 3){
							printf("Error: illegal move :(\n");
						}
					}
				}
			}
			break;
		default:
			printf("error: wrong input in function printBoard()");
	}

	move++;
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

	while(gameFinish == 0){
		system("clear");

		int startValueY, destinationValueY;
		char moveInput[8];

		printf("%s", gameBanner);

		printBoard(mainBoard, boardOrientation, movePiecesReturn);

		// take move input
		printf("your move: ");
		fgets(moveInput, 8, stdin);

		if(moveInput[0] == 'q' && moveInput[1] == 'u' && moveInput[2] == 'i' && moveInput[3] == 't'){
			gameFinish = 1;
		} else if (moveInput[0] == 'r' && moveInput[1] == 'e' && moveInput[2] == 's' && moveInput[3] == 'e' && moveInput[4] == 't'){
			startGame(gameOrientation);
		} else {
			// input string: "2:h-5:f"
			startValueY = atoi(&moveInput[0]);
			destinationValueY = atoi(&moveInput[4]);

			movePiecesReturn = movePieces(mainBoard, startValueY-1, moveInput[2], destinationValueY-1, moveInput[6]);
		}
	}

	printf("\nGAME FINISHED\n");
}

void logPage(){
	system("clear");
	printf("%s", gameBanner);

	int inputChoise;
	char inputName[16];
	char inputPass[16];

	printf("\n");
	printf("1: login \n");
	printf("2: register \n");
	printf("> ");

	scanf("%d", inputChoise);
	
	switch(inputChoise){
		case 1:
			system("clear");
			printf("%s", gameBanner);
			
			printf("\n");
			printf("Insert your username: ");
			fgets(inpuName, 16, stdin);

			printf("Insert your passowrd: ");
			fgest(inputPass, 16, stdin);

			break;
		case 2:
			
			break;
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
	logPage(){
		
	}
	//menu();
}

