#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constantes
#define EMPTY 0
#define BOARD_SIZE 4
#define RIGHT 'd';
#define LEFT 'a';
#define UP 'w';
#define DOWN 's';
#define NEW_NUMBER 2;

//Definicion de las funciones // 
void initializeBoard();		//Inicializa el tablero.
void printBoard();			//Funcion que imprime el tablero.
void placeNewNumber();		//Funcion que coloca un numero en un lugar libre.
int checkForFreeSpaces();	//Funcion que retorna 1 si existe al menos un lugar vacio, 0 si no.
char movement();			//Funcion que mueve y retorna que movimiento se introdujo.
int gameOver();				//Determina si el juego finalizo.
int checkToJoin(char);		//Revisa de acuerdo al movimiento si hay fichas para unir y retorna el valor de las fichas unidas.

int board[BOARD_SIZE][BOARD_SIZE];

int main(){
	int points = 0;
	int winOrLose = 0;
	char c;
	initializeBoard();
	// while(!(winOrLose = gameOver())){
	// 	points += checkToJoin(movement());
	// 	placeNewNumber();
	// 	printBoard();
	// 	printf("Puntos: %d\n",points);
	// }
	// if (winOrLose == 1)
	// 	printf("Has Ganado!\n");
	// else
	// 	printf("Has Perdido!\n");
	printBoard();
	while(1){
		c = movement();
		placeNewNumber();
		printBoard();
	}
	
	return 0;
}	

void printBoard(){
	int i,j;
	for(j = 0; j < BOARD_SIZE; j++)
			printf(" _______");
	printf("\n");
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			if (board[i][j] != EMPTY)
				printf("| %d\t",board[i][j]);
			else
				printf("| \t");
		}
		printf("|\n");
		for(j = 0; j < BOARD_SIZE; j++)
			printf(" _______");
		printf("\n");
	}
}

void initializeBoard(){
	int i,j;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++){
			board[i][j] = EMPTY;
		}
	}
	placeNewNumber();
	placeNewNumber();
}

void placeNewNumber(){
	int i,j;
	srand(time(NULL));
	if (checkForFreeSpaces()){
		while(board[(i=rand()%4)][j=(rand()%4)] != EMPTY)
		;
		board[i][j] = NEW_NUMBER;
	}
}

int checkForFreeSpaces(){
	int i,j,freeSpace = 0;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == EMPTY){
				freeSpace = 1;
				break;
			}
		if (freeSpace)
			break;
	}
	return freeSpace;
}

char movement(){
	char move;
	int i,j,flag,aux;//flag es para seguir moviendo hasta el tope.
	move = getchar();
	while (move != UP && move != DOWN && move != RIGHT && move != LEFT){
		printf("Tecla invalida, intente de nuevo.");
		move = getchar();
	}
	switch (move){
		case RIGHT:
			flag = 1;
			while (flag){
				flag = 0;
				for(i = 0; i < BOARD_SIZE; i++){
					for(j = BOARD_SIZE; j > 0; j--){
						if(board[i][j] == EMPTY && board[i][j-1] != EMPTY){
							aux = board[i][j];
							board[i][j] = board[i][j-1];
							board[i][j-1] = aux;
							flag = 1;
						}
					}
				}
			}
		break;//END CASE RIGHT
		default:
			printf("No se puede mover en esa direccion\n");
		break;//END DEFAULT
	}
	return move;
}