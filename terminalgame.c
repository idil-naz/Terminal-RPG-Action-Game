#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<conio.h>

int positionx = 0; //Global variables
int positiony = 0;
int position[2];

void prepareDisplayMatrix(int row, int column, char displayMatrix[row][column]);
void display(int row, int column, char displayMatrix[row][column], char discoveredPath[row][column]);
void preparePlacementMatrix(int row, int column, char placementMatrix[row][column], int treeCount, int enemyCount);
void updateDisplayMatrix(int row, int column, char displayMatrix[row][column], char placementMatrix[row][column], char inputCharacter);
void fightWithTheEnemy(int row,int column, char placementMatrix[row][column], char inputCharacter, int *enemyCount);
void update(int row, int column, char displayMatrix[row][column], char placementMatrix[row][column], int enemyCount, char discoveredPath[row][column]);
void updateDiscoveredPath(int row, int column, char displayMatrix[row][column], char discoveredPath[row][column]);
void displayGodMode(int row, int column, char displayMatrix[row][column], char placementMatrix[row][column]);             //Function prototypes

int main(){

	int row = 20;
	int column = 30; //Row and column variable definitions

	char displayMatrix[row][column];
	char placementMatrix[row][column];  //Display and placement matrices

	int treeCount = 5;
	int enemyCount = 5; //Tree and enemy variables initialization

	char discoveredPath[row][column];
	
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			discoveredPath[i][j] = '-';
		}
	}
	
	prepareTheGame(row, column, displayMatrix, placementMatrix, treeCount, enemyCount);
	update(row, column, displayMatrix, placementMatrix, enemyCount, discoveredPath);
	
	return 0;
}

void prepareDisplayMatrix(int row, int column, char displayMatrix[row][column]){

		for(int i=0; i<row; i++){
			for(int j=0; j<column; j++){

			if(i == position[1] && j == position[0]) displayMatrix[i][j] = 'P';

			else displayMatrix[i][j] = -78;
			}
		}
}

void preparePlacementMatrix(int row, int column, char placementMatrix[row][column], int treeCount, int enemyCount){

	int randomTreeX, randomTreeY;
	int randomEnemyX, randomEnemyY;

		for(int i=0; i<row; i++){
			for(int j=0; j<column; j++){
				placementMatrix[i][j] = ' ';
			}
		}
		for(int i=0; i<treeCount; i++){
			randomTreeX = 3 + rand()%(30 - 3);
			randomTreeY = 3 + rand()%(20 - 3);

			placementMatrix[randomTreeY][randomTreeX] = 'T';
		}
		for(int i=0; i<enemyCount; i++){
			randomEnemyX = 3 + rand()%(30 - 3);
			randomEnemyY = 3 + rand()%(20 - 3);

			placementMatrix[randomEnemyY][randomEnemyX] = 'E';
		}
}

void display(int row, int column, char displayMatrix[row][column], char discoveredPath[row][column]){

	system("cls");

	for(int i=0; i<row; i++){
		printf("\n");
		for(int j=0; j<column; j++){
			printf("%c", displayMatrix[i][j]);
		}
	}
	printf("\n");
}

void update(int row, int column, char displayMatrix[row][column], char placementMatrix[row][column], int enemyCount, char discoveredPath[row][column]){

	char inputCharacter;
	int toggle=0;

	while(inputCharacter != 'q' && enemyCount > 0){

		if(toggle == 0){
            display(row,column,displayMatrix, discoveredPath);
		}
		else{
			
            	if(toggle % 2 == 1){
                displayGodMode(row,column,displayMatrix,placementMatrix);
           	 	}
           			else if(toggle % 2 == 0){
               			 for(int i=0; i<row; i++){
							for(int j=0; j<column; j++){
								if(discoveredPath[i][j] == '+'){
									displayMatrix[i][j] == -80;
									}		
					else if(discoveredPath[i][j] == '-'){
						displayMatrix[i][j] = -78;
						}
					}
				}
				
display(row,column,displayMatrix, discoveredPath);
			
        		}
			}
			
inputCharacter = getch();

		if(inputCharacter == 'c' || inputCharacter == 'C'){
            toggle++;
		}
		
		fightWithTheEnemy(row, column, placementMatrix,inputCharacter, &enemyCount);
		updateDisplayMatrix(row, column, displayMatrix, placementMatrix, inputCharacter);
		updateDiscoveredPath(row, column, displayMatrix, discoveredPath);
		
		if(enemyCount == 0) printf("\n***Well done! You have defeated all the enemies!***");
		
	}
}

void updateDisplayMatrix(int row, int column, char displayMatrix[row][column], char placementMatrix[row][column], char inputCharacter){

	int previousPosition_x = positionx;
	int previousPosition_y = positiony;

	if(inputCharacter == 'w' || inputCharacter == 'W') {positiony -= 1; position[1] = positiony;}            //MOVEMENT KEYS INPUT
	else if(inputCharacter == 'a' || inputCharacter == 'A') {positionx -= 1; position[0] = positionx;}
	else if(inputCharacter == 's' || inputCharacter == 'S') {positiony += 1; position[1] = positiony;}
	else if(inputCharacter == 'd' || inputCharacter == 'D') {positionx += 1; position[0] = positionx;}

	displayMatrix[positiony - 1][positionx] = -80;      //FOG OF WAR
	displayMatrix[positiony - 1][positionx + 1] = -80;
	displayMatrix[positiony - 1][positionx - 1] = -80;

	displayMatrix[positiony][positionx - 1] = -80;
	displayMatrix[positiony][positionx + 1] = -80;

	displayMatrix[positiony + 1][positionx - 1] = -80;
	displayMatrix[positiony + 1][positionx] = -80;
	displayMatrix[positiony + 1][positionx + 1] = -80;

	if((positionx > 29 || positionx < 0) || (positiony > 19 || positiony < 0) || (placementMatrix[positiony][positionx] != ' ')){ //WALL
		positiony = previousPosition_y;
		positionx = previousPosition_x;
	}

	displayMatrix[positiony][positionx] = 'P';

	for(int i = 0;i < row;i++){ 		//TREE AND ENEMY SPAWN
    for(int j = 0;j < column;j++){
        if(displayMatrix[i][j] == -80 && placementMatrix[i][j]!= ' '){
            displayMatrix[i][j] = placementMatrix[i][j];
       	 	}
   	 	}
	}
}

void updateDiscoveredPath(int row, int column, char displayMatrix[row][column], char discoveredPath[row][column]){
	
	if(positionx == 0 && positiony == 0){
		
	discoveredPath[positiony][positionx + 1] = '+';
	discoveredPath[positiony + 1][positionx] = '+';
	discoveredPath[positiony + 1][positionx + 1] = '+';
	
	}
	
	else if(positionx == 0 && positiony == 19){
		
	discoveredPath[positiony - 1][positionx] = '+';
	discoveredPath[positiony - 1][positionx + 1] = '+';
	discoveredPath[positiony][positionx + 1] = '+';
	
	}
	
	else if(positionx == 29 && positiony == 0){

	discoveredPath[positiony][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx] = '+';
	
	}
	
	else if(positionx == 29 && positiony == 19){

	discoveredPath[positiony][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx] = '+';

	}
	
	else if(positionx == 0){
		
	discoveredPath[positiony - 1][positionx] = '+';
	discoveredPath[positiony - 1][positionx + 1] = '+';
	discoveredPath[positiony][positionx + 1] = '+';
	discoveredPath[positiony + 1][positionx] = '+';
	discoveredPath[positiony + 1][positionx + 1] = '+';
	
	}
	
	else if(positionx == 29){
		
	discoveredPath[positiony - 1][positionx] = '+';
	discoveredPath[positiony - 1][positionx - 1] = '+';
	discoveredPath[positiony][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx] = '+';

	}
	
	else if(positiony == 0){
	
	discoveredPath[positiony][positionx - 1] = '+';
	discoveredPath[positiony][positionx + 1] = '+';
	discoveredPath[positiony + 1][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx] = '+';
	discoveredPath[positiony + 1][positionx + 1] = '+';
	
	}
	
	else if(positiony == 19){
		
	discoveredPath[positiony - 1][positionx] = '+';
	discoveredPath[positiony - 1][positionx + 1] = '+';
	discoveredPath[positiony - 1][positionx - 1] = '+';
	discoveredPath[positiony][positionx - 1] = '+';
	discoveredPath[positiony][positionx + 1] = '+';
	
	}

	else{
		
	discoveredPath[positiony - 1][positionx] = '+';
	discoveredPath[positiony - 1][positionx + 1] = '+';
	discoveredPath[positiony - 1][positionx - 1] = '+';
	discoveredPath[positiony][positionx - 1] = '+';
	discoveredPath[positiony][positionx + 1] = '+';
	discoveredPath[positiony + 1][positionx - 1] = '+';
	discoveredPath[positiony + 1][positionx] = '+';
	discoveredPath[positiony + 1][positionx + 1] = '+';
	
	}
	
	for(int i = 0; i<row; i++){
		for(int j = 0; j < column; j++){
			if(displayMatrix[i][j] == '+' || displayMatrix[i][j] == '-'){
				displayMatrix[i][j] = -80;
			}
		}
	}
	
}

void prepareTheGame(int row, int column, char displayMatrix[row][column], char placementMatrix[row][column], int treeCount, int enemyCount){

	prepareDisplayMatrix(row,column,displayMatrix);
	srand(time(0));
	preparePlacementMatrix(row, column, placementMatrix, treeCount, enemyCount);
}

void fightWithTheEnemy(int row,int column, char placementMatrix[row][column], char inputCharacter, int *enemyCount){ //ENEMY HITTING

	if(placementMatrix[positiony - 1][positionx] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony - 1][positionx] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}

	else if(placementMatrix[positiony - 1][positionx + 1] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony - 1][positionx + 1] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}

	else if(placementMatrix[positiony - 1][positionx - 1] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony - 1][positionx - 1] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}

	else if(placementMatrix[positiony][positionx - 1] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony][positionx - 1] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}
	
	else if(placementMatrix[positiony][positionx + 1] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony][positionx + 1] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}

	else if(placementMatrix[positiony + 1][positionx - 1] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony + 1][positionx - 1] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}

	else if(placementMatrix[positiony + 1][positionx] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony + 1][positionx] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}

	else if(placementMatrix[positiony + 1][positionx + 1] == 'E'){
		if(inputCharacter == 'H' || inputCharacter == 'h'){
			placementMatrix[positiony + 1][positionx + 1] = ' ';
			*enemyCount = *enemyCount - 1;
		}
	}
}

void displayGodMode(int row, int column, char displayMatrix[row][column], char placementMatrix[row][column]){
	
    system("cls");
    
	for(int i = 0; i < row; i++){
		for(int j = 0; j < column; j++){
			if(displayMatrix[i][j] == -78 && displayMatrix[i][j] != 'P') displayMatrix[i][j] = placementMatrix[i][j];
			if(placementMatrix[i][j] == ' ' && displayMatrix[i][j] != 'P') displayMatrix[i][j] = -80;
		}
	}
	
	for(int i = 0; i < row; i++){
		printf("\n");
		for(int j = 0; j < column; j++){
			printf("%c", displayMatrix[i][j]);
		}
	}
}