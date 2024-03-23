#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#define MAX_SIZE 100
int main() {
  int s;
  struct sockaddr_in server, client;
  int c, l;
  uint16_t client_numbers1[MAX_SIZE];
  uint16_t client_numbers2[MAX_SIZE];
  uint16_t common_numbers[MAX_SIZE];

  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    printf("Eroare la crearea socketului server\n");
    return 1;
  }

  memset(&server, 0, sizeof(server));
  server.sin_port = htons(53293);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;

  if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0) {
    printf("Eroare la bind\n");
    return 1;
  }

  listen(s, 5);

  l = sizeof(client);
  memset(&client, 0, sizeof(client));

  while (1) {
    int num1, num2,i,j,sir_numere[MAX_SIZE];
	int k=0;
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului

    recv(c, &num1, sizeof(num1), MSG_WAITALL);
        num1=ntohl(num1);
    printf("primit lungimea listei %d \n",num1);
   
          for (i = 0; i < num1; i++) {
        recv(c, &sir_numere[i], sizeof(sir_numere[i]), MSG_WAITALL);
		k=k+sir_numere[i];
    }
printf("citit primele numere\n");
     
	
	printf("suma numere \n");
printf("%d\n",k); 
	 
k=htonl(k);

        send(c, &k, sizeof(k), 0);
printf("s-a trimis k \n");
   
    close(c);
    // sfarsitul deservirii clientului;
  }
}
