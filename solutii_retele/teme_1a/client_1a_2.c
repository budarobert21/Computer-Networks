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
   int i,j,n,m,len;
   char sir[MAX_SIZE];

	printf("DATI SIRUL: ");
	fgets(sir,sizeof(sir),stdin);
	sir[strlen(sir)-1]= '\0';  //important pentru a finaliza sirul
	
	len=strlen(sir);
	len=htonl(len);
	printf("lungimea= %d \n",ntohl(len));
	send(c,&len,sizeof(int),0); //trimitem lungimea sirului
	printf("trimitem tot sirul\n");
	send(c,&sir,ntohl(len)*sizeof(char),0); //trimitem tot sirul
	
	int nr_spatii;
	recv(c,&nr_spatii,sizeof(int),MSG_WAITALL);
	nr_spatii=ntohl(nr_spatii);
	printf("numarul spatiilor este = %d \n",nr_spatii);
    


  close(c);
}
