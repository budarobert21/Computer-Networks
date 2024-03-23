#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#define MAX_SIZE 100
int main() {
 //trimit un sir de numere -> suma numerelor
  struct sockaddr_in server;
  int c;
  
        //merge si cu int uri doar ca nu mai facem cu htons care e short ...ci cu htonl
  c = socket(AF_INET, SOCK_STREAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(53293);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");

  if (connect(c, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la conectarea la server\n");
    return 1;
  }
   int i,j,n,m,len1,len2;
   char car;
   int numar_aparitii;
   char sir1[MAX_SIZE];
   char sir2[MAX_SIZE];

	printf("DATI SIRUL 1: ");
	fgets(sir1,sizeof(sir1),stdin);
	sir1[strlen(sir1)-1]= '\0';  //important pentru a finaliza sirul
	
	len1=strlen(sir1);
	len1=htonl(len1);
	printf("lungimea= %d\n",ntohl(len1));
	send(c,&len1,sizeof(int),0); //trimitem lungimea sirului  //trimis lungime
	printf("trimitem tot sirul \n");
	send(c,&sir1,ntohl(len1)*sizeof(char),0); //trimitem tot sirul //trimis sir
	
	printf("DATI SIRUL 2: ");
	fgets(sir2,sizeof(sir2),stdin);
	sir2[strlen(sir2)-1]= '\0';  //important pentru a finaliza sirul
	
	len2=strlen(sir2);
	len2=htonl(len2);
	printf("lungimea= %d\n",ntohl(len2));
	send(c,&len2,sizeof(int),0); //trimitem lungimea sirului
	printf("trimitem tot sirul \n");
	send(c,&sir2,ntohl(len2)*sizeof(char),0); //trimitem tot sirul
	
	
	
	
	 recv(c, &car, sizeof(char), MSG_WAITALL);	 
	 recv(c, &numar_aparitii, sizeof(int), MSG_WAITALL);	 
	numar_aparitii=ntohl(numar_aparitii);		
		
		printf("caracterul: %c \n",car);
		printf("a aparut de :%d \n",numar_aparitii);
		
    
	

  close(c);
}
