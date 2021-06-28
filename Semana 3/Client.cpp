#include <windows.h>
#include <winsock.h>
#include <stdio.h>
#include <string.h>

#define REMOTE_SERVER_PORT 2018
#define SERVIDOR "127.0.0.1"
#define BUFFER_LENGTH 4096


int main() {
	
	int sd;
	struct sockaddr_in cliAddr, remoteServAddr;
	WSADATA wsaData;
	LPHOSTENT lpHostEntry; 
	char mensagem[BUFFER_LENGTH];
	
	WSAStartup(MAKEWORD(2,1),&wsaData);
	
	lpHostEntry = gethostbyname(SERVIDOR);
	
	/* Criação do socket */
	sd = socket(AF_INET,SOCK_DGRAM,0);
	
	if(sd < 0) {
		printf("Nao foi possivel criar o socket com o servidor %s:\n",SERVIDOR);
		exit(1);
	}
	
	/* Bind */
	cliAddr.sin_family = AF_INET;
	cliAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	cliAddr.sin_port = htons(0);
	
	remoteServAddr.sin_family = AF_INET;
	remoteServAddr.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list);
	remoteServAddr.sin_port = htons(REMOTE_SERVER_PORT);	


	FILE *txt;
	if((txt = fopen("Arquivo.txt",  "r+")) == NULL){
		printf("Erro ao abrir arquivo!");
	}else{
		FILE *txt2;
		if((txt2 = fopen("ArquivoRecebidoMaiuscula.txt", "w+")) == NULL){
			printf("Erro ao abrir arquivo de recebimento!\n");
		}else{
			while(!feof(txt)){
				fgets(mensagem, BUFFER_LENGTH, txt);

			  	if(sendto(sd, mensagem, strlen(mensagem)+1, 0,(LPSOCKADDR) &remoteServAddr, sizeof(struct sockaddr)) < 0) {
					printf("Nao foi possivel enviar a mensagem\n");
			    	closesocket(sd);
			    	exit(1);
			    }
			    
			    printf("Mensagem enviada para o servidor: %s\n", mensagem);
				
				memset(mensagem, 0, strlen(mensagem));
				int servLen = sizeof(remoteServAddr);
			    if(recvfrom(sd, mensagem, BUFFER_LENGTH, 0, (struct sockaddr *) &remoteServAddr, &servLen) < 0) {
			    	printf("Nao foi possivel receber dados");
			    	continue;
			    }
				
				printf("Mensagem recebida: %s\n", mensagem);
				fprintf(txt2, "%s", mensagem);
				memset(mensagem, 0, strlen(mensagem));
			}
			fclose(txt);
			fclose(txt2);
		}
	}
	system("pause");
	
	closesocket(sd);
	return 1;

}
