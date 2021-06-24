#include<stdio.h>
#include<stdlib.h>

//Método para contar de 1 a 9000000 procedural
void multiplos(int valor){
	FILE *txt;
	char nome_do_arquivo[30];
	
	//Renomeando o arquivo de acordo com o multiplo desejado
	snprintf (nome_do_arquivo, sizeof(nome_do_arquivo), "MultiplosDe%d.txt", valor);
	
	if((txt = fopen(nome_do_arquivo, "w")) == NULL){
		printf("Erro ao abrir o arquivo!");
	}else{
		printf("Multiplos de %i...\n\n", valor);
		
		for(int i = 1; i <= 9000000; i++){
			if(i % valor == 0){
				fprintf(txt, "%i\n", i);
				
				//Não lembro se é para printar ou não, mas caso não seja, só apagar esse printf xD
				//printf("%i\n", i);
			}
		}
	}
	fclose(txt);
}

int main(){
	
	multiplos(3);
	multiplos(5);
	multiplos(7);
	multiplos(9);
	
	return 0;
}
