#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<ctype.h>
#include "mpi.h"

struct dicionario{
	char palavra[100];
}typedef Dicionario;

void procura_palindromos(Dicionario *d, Dicionario *penviados){
	int i, j, x, y = 0, z;
	char buffer[100], buffernormalizado[100], bufferinvertido[100];
	for(z = 0; d[z].palavra[0] != '\0'; z++){
		//Copio as palavras salvas no meu dicionario para poder verificar se s√£o ou n√£o palindromos.
	    strcpy(buffer, d[z].palavra);
	    
		j = 0;
	    //Normalizando as palavras para ignorar acentua√ß√£o, letras minusculas e maiusculas e hÌfen.
	    for(i=0; i<strlen(buffer); i++){
			//Convertendo tudo para minusculo.
			buffer[i] = tolower(buffer[i]);
			
			//Ignorando hÌfen
			if(buffer[i] != '-'){
			    buffernormalizado[j] = buffer[i];
			    j++;
			}
	    }
	    //Fun√ß√£o para inverter a palavra.
	    j = strlen(buffernormalizado) - 1;

	    for(x = 0; x < strlen(buffernormalizado); x++){
			bufferinvertido[j] = buffernormalizado[x];
			j--;
	    }
	    
	    //Conferindo se s„o iguais, se sim, eu salvo na minha lista de palindromos.
	    if(strcmp(bufferinvertido, buffernormalizado) == 0){
			strcpy(penviados[y].palavra, d[z].palavra);
			y++;
	    }
	    memset(buffer, 0, sizeof(buffer));
	    memset(bufferinvertido, 0, sizeof(bufferinvertido));
	    memset(buffernormalizado, 0, sizeof(buffernormalizado));
	}
	penviados[y].palavra[0] = '\0';
}

main(int argc, char **argv ) {
	int rank, size;
	MPI_Status status;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	//N„o consegui com estruturas, ent„o achei essa soluÁ„o
	Dicionario dic[1000];
	Dicionario recebido[1000];
	Dicionario palindromosRecebidos[150];
	Dicionario palindromosEnviados[150];
	FILE *txt;
	int i, y, aux = 1000, type = 99;
	int tam, index;

	if(size > 1){
		tam =  1000 / (size - 1);
	}
	if (rank == 0){ //Se for 0 ent„o estou no cluster master, portanto eu abro o arquivo e leio todas as palavras.
		if((txt = fopen("dicionario.txt", "r")) == NULL){
			printf("Erro na leitura.\n");
		}else{
			y = 1;
			index = 0;
			for(i = 0; !feof(txt); i++){
				/*
					Vai sempre dividir o total de palavras pela quantidade de clusters - 1, j· que o master sÛ vai ler
					e os escravos que v„o resolver os palindromos. (FUNCIONANDO)
				*/
				if(size > 1){
					fscanf(txt, " %s", dic[index].palavra);
					if(y < size - 1 && i == (tam * y) - 1){
						dic[index + 1].palavra[0] = '\0';
						MPI_Send(dic, sizeof(dic), MPI_CHAR, y, type, MPI_COMM_WORLD);
						y++;
						index = 0;
						memset(dic, 0, sizeof(dic));
					}else{
						index++;
					}
					if(y == size - 1 && i == 999){
						dic[index].palavra[0] = '\0';
						MPI_Send(dic, sizeof(dic), MPI_CHAR, y, type, MPI_COMM_WORLD);
						y = 1;
					}
				}else{
					fscanf(txt, " %s", dic[i].palavra);
				}
			}
		}
		fclose(txt);
		
		//Depois recebo as palavras palindromas. (testar)
		if((txt = fopen("lista-palindromos.txt", "w")) == NULL){
			printf("Erro na criacao do arquivo.\n");
		}else{
			Dicionario aux[150];
			int indexaux;
			if(size > 1){
				indexaux = 0;
				for (i = 1; i < size; i++){
					MPI_Recv(aux, sizeof(aux), MPI_CHAR, i, type, MPI_COMM_WORLD, &status);
					for(y = 0; aux[y].palavra[0] != '\0'; y++){
						strcpy(palindromosRecebidos[indexaux].palavra, aux[y].palavra);
						printf("Palindromo recebido do processo %i: %s\n", i, palindromosRecebidos[indexaux].palavra);
						fprintf(txt, " %s\n", palindromosRecebidos[indexaux].palavra);
						indexaux++;
					}
				}
				printf("\nTotal de %i palindromos\n", indexaux);
			}
			if(size == 1){
			//Nesse caso sÛ tem 1 cluster, no caso quem vai fazer tudo vai ser o master
				dic[1000].palavra[0] = '\0';
				procura_palindromos(dic, palindromosEnviados);
				for(i = 0; palindromosEnviados[i].palavra[0] != '\0'; i++){
					fprintf(txt, " %s\n", palindromosEnviados[i].palavra);
					printf("Palindromo encontrado pelo master: %s\n", palindromosEnviados[i].palavra);
				}
					printf("\nTotal de %i palindromos\n", i);
			}
		}
		fclose(txt);
		
		
	}else{ // Caso n„o seja o cluster master, ent„o eu estou no escravo.
		printf("Processo %d recebeu o vetor\n", rank);
		MPI_Recv(recebido, sizeof(recebido), MPI_CHAR, 0, type, MPI_COMM_WORLD, &status);
		procura_palindromos(recebido, palindromosEnviados);
		MPI_Send(palindromosEnviados, sizeof(palindromosEnviados), MPI_CHAR, 0, type, MPI_COMM_WORLD);
	}

	MPI_Finalize(); 
}

