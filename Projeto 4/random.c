#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int main() {

	int diceRoll;
	int memory[6];
	srand(time(NULL));

	printf("\t\t\t Welcome to Dice Game!\n");

	for(int i=0; i<6; i++){
		diceRoll = (rand()%6)+1;
		for(int j=i; j>=0; j--){
			if(diceRoll==memory[j]){
				diceRoll = (rand()%6)+1;
				j=i;	
			}
		}
		memory[i]=diceRoll;
		printf(" %d \n", diceRoll);
	}

	return 0;

}
