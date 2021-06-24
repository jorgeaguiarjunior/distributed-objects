#include <stdio.h>  
#include <pthread.h>  
#include <unistd.h> 
#include <stdlib.h>
#include <time.h>

//Método para contar de 1 a 9000000 com threads
void *multiplos(void *th){
	FILE *txt;
	char nome_do_arquivo[30];
	int valor = *((int*)(&th));
	
	//Renomeando o arquivo de acordo com o multiplo desejado
	snprintf (nome_do_arquivo, sizeof(nome_do_arquivo), "MultiplosDe%d.txt", valor);
	
	if((txt = fopen(nome_do_arquivo, "w")) == NULL){
		printf("Erro ao abrir o arquivo!");
	}else{
		printf("Multiplos de %i:\n\n", valor);
		
		for(int i = 1; i <= 9000000; i++){
			if(i % valor == 0){
				fprintf(txt, "%i\n", i);
				
				//Não lembro se é para printar ou não, mas caso não seja, só apagar esse printf xD
				//printf("%i\n", i);
			}
		}
	}
	fclose(txt);
   	pthread_exit(NULL);
}


int main (){   
	pthread_t threads[4];
	printf("Criando Threads!\n\n");
			
	pthread_create(&threads[0],NULL,multiplos,(void *)3);
	pthread_create(&threads[1],NULL,multiplos,(void *)5);
	pthread_create(&threads[2],NULL,multiplos,(void *)7);
	pthread_create(&threads[3],NULL,multiplos,(void *)9);
			
	pthread_exit(NULL);
	return 0;   
}
