#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Constantes
#define EMPTY 0
#define BOARD_SIZE 4
#define RIGHT 'd'
#define LEFT 'a'
#define UP 'w'
#define DOWN 's'
#define NEW_NUMBER 2
#define WIN 2048

//Definicion de las funciones // 
void initializeBoard();		//Inicializa el tablero.
void printBoard();			//Funcion que imprime el tablero.
void placeNewNumber();		//Funcion que coloca un numero en un lugar libre.
int checkForFreeSpaces();	//Funcion que retorna 1 si existe al menos un lugar vacio, 0 si no.
char movement();			//Funcion que mueve y retorna que movimiento se introdujo.
int gameOver();				//Determina si el juego finalizo.
int checkToJoin(char,int);		//Revisa de acuerdo al movimiento si hay fichas para unir y retorna el valor de las fichas unidas.

int board[BOARD_SIZE][BOARD_SIZE];

int main(){
	int points = 0;
	int winOrLose = 0;
	initializeBoard();
	printBoard();
	while(!(winOrLose = gameOver())){
		printf("Introduzca su movimiento:");
		points += checkToJoin(movement(),0);
		placeNewNumber();
		printBoard();
		printf("Puntos: %d\n",points);
	}
	if (winOrLose == 1)
		printf("Has Ganado!\n");
	else
		printf("Has Perdido!\n");	
	return 0;
}	

void printBoard(){
	int i,j;
	printf("*********************************\n");
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
	printf("\n*********************************\n");
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
	int i,j,flag = 0;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE; j++)
			if (board[i][j] == EMPTY){
				flag = 1;
			}
	}
	return flag;
}

char movement(){
	char move;
	int i,j,flag,aux;//flag es para seguir moviendo hasta el tope.
	scanf("%c",&move);
	getchar();
	while (move != UP && move != DOWN && move != RIGHT && move != LEFT){
		printf("Tecla invalida, intente de nuevo.");
		scanf("%c",&move);
		getchar();
	}
	switch (move){
		case RIGHT:
			flag = 1;
			while (flag){
				flag = 0;
				for(i = 0; i < BOARD_SIZE; i++){
					for(j = BOARD_SIZE-1; j > 0; j--){
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
		case LEFT:
			flag = 1;
			while (flag){
				flag = 0;
				for(i = 0; i < BOARD_SIZE; i++){
					for(j = 0; j < BOARD_SIZE - 1; j++){
						if(board[i][j] == EMPTY && board[i][j+1] != EMPTY){
							aux = board[i][j];
							board[i][j] = board[i][j+1];
							board[i][j+1] = aux;
							flag = 1;
						}
					}
				}
			}
			break;//END CASE LEFT
		case UP:
			flag = 1;
			while (flag){
				flag = 0;
				for(j = 0; j < BOARD_SIZE; j++){
					for(i = 0; i < BOARD_SIZE - 1; i++){
						if(board[i][j] == EMPTY && board[i+1][j] != EMPTY){
							aux = board[i][j];
							board[i][j] = board[i+1][j];
							board[i+1][j] = aux;
							flag = 1;
						}
					}
				}
			}
			break;//END CASE UP
		case DOWN:
			flag = 1;
			while (flag){
				flag = 0;
				for(j = 0; j < BOARD_SIZE; j++){
					for(i = BOARD_SIZE - 1; i > 0 ; i--){
						if(board[i][j] == EMPTY && board[i-1][j] != EMPTY){
							aux = board[i][j];
							board[i][j] = board[i-1][j];
							board[i-1][j] = aux;
							flag = 1;
						}
					}
				}
			}
			break;//END CASE DOWN
		default:
			printf("No se puede mover en esa direccion\n");
			break;//END DEFAULT
	}
	return move;
}

int checkToJoin(char move,int checkIf){
	int i,j,flag,aux,points = 0, joined;//flag es para seguir moviendo hasta el tope.
	switch (move){
		case RIGHT:
			for(i = 0; i < BOARD_SIZE; i++){
				joined = 0;
				for(j = BOARD_SIZE-1; j > 0; j--){
					if(board[i][j] == board[i][j-1] && !joined){
						if(checkIf)
							return 1;
						board[i][j] += board[i][j-1];
						board[i][j-1] = EMPTY;
						points += board[i][j];
						joined = 1;
					}
					if(board[i][j] == EMPTY && board[i][j-1] != EMPTY){
						aux = board[i][j];
						board[i][j] = board[i][j-1];
						board[i][j-1] = aux;
					}
				}
			}
			break;//END CASE RIGHT
		case LEFT:
			for(i = 0; i < BOARD_SIZE; i++){
				joined = 0;
				for(j = 0; j < BOARD_SIZE - 1; j++){
					if(board[i][j] == board[i][j+1] && !joined){
						if(checkIf)
							return 1;
						board[i][j] += board[i][j+1];
						board[i][j+1] = EMPTY;
						points += board[i][j];
						joined = 1;
					}
					if(board[i][j] == EMPTY && board[i][j+1] != EMPTY){
						aux = board[i][j];
						board[i][j] = board[i][j+1];
						board[i][j+1] = aux;
					}
				}
			}
			break;//END CASE LEFT
		case UP:
			for(j = 0; j < BOARD_SIZE; j++){
				joined = 0;
				for(i = 0; i < BOARD_SIZE - 1; i++){
					if(board[i][j] == board[i+1][j] && !joined){
						if(checkIf)
							return 1;
						board[i][j] += board[i+1][j];
						board[i+1][j] = EMPTY;
						points += board[i][j];
						joined = 1;
					}
					if(board[i][j] == EMPTY && board[i+1][j] != EMPTY){
						aux = board[i][j];
						board[i][j] = board[i+1][j];
						board[i+1][j] = aux;
						flag = 1;
					}
				}
			}
			break;//END CASE UP
		case DOWN:
			for(j = 0; j < BOARD_SIZE; j++){
				joined = 0;
				for(i = BOARD_SIZE - 1; i > 0 ; i--){
					if(board[i][j] == board[i-1][j] && !joined){
						if(checkIf)
							return 1;
						board[i][j] += board[i-1][j];
						board[i-1][j] = EMPTY;
						points += board[i][j];
						joined = 1;
					}
					if(board[i][j] == EMPTY && board[i-1][j] != EMPTY){
						aux = board[i][j];
						board[i][j] = board[i-1][j];
						board[i-1][j] = aux;
						flag = 1;
					}
				}
			}
			break;//END CASE DOWN
		default:
			printf("No se encontro uniones en esa direccion\n");
			break;//END DEFAULT
	}
	return points;
}

int gameOver(){
	int i,j,lost = 0;
	for(i = 0; i < BOARD_SIZE; i++){
		for(j = 0; j < BOARD_SIZE - 1; j++){
			if (board[i][j] == WIN)
				return 1;
		}
	}
	if (checkForFreeSpaces())
		return 0;
	else{
		lost = lost + checkToJoin(UP,1) + checkToJoin(DOWN,1) + checkToJoin(LEFT,1) + checkToJoin(RIGHT,1);
		
		if(!lost)
			return 2;
		else 
			return 0;
	}

}