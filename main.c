#include <stdio.h>

void startGame(){
	printf("\n\n game started");
}

void quit(){
	printf("not avalable");
}

// menu
int main(){
	int inputChoise;
	
	printf("chess game v1.0 \n");
	printf("1: start a game \n");
	printf("2: quit \n");

	scanf("%d", inputChoise);

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
