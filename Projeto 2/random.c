#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void get_random_file(char * file_name, char * file_path);
//Função gera 25 nomes de arquivo aleatório entre os apresentados
int main()
{
	srand(time(0));	// Usado para rand() gerar número aleátorio cada vez que rodado

	char files_names[25][50];
	char files_path[25][50];
	for(int i=0; i<25; i++){
		get_random_file(files_names[i], files_path[i]);
		printf("%s\n", files_path[i]);
	}
	return 0;

}
void get_random_file(char * file_name, char * file_path){
	
	
	char data_type[50]; 
	int random_2 = (rand()%2)+1; //Gera número aleatório de 1 a 2 
	//O número gerado determina o tipo de arquivo
	if(random_2==1){
		strcpy(data_type, "asphalt");
	}
	else{
		strcpy(data_type, "grass");
	}
	int random_50 = (rand()%50)+1; //Gera número aleatório de 1 a 50 
	sprintf(file_name ,"%s_%02d.txt", data_type, random_50);
	sprintf(file_path ,"./DataSet/%s/%s", data_type, file_name);
	
}


