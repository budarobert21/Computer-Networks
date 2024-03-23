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
   int i,j,n,m;
   int arr1[MAX_SIZE];

  printf("n = ");
  scanf("%d", &n);


  n=htonl(n);
  send(c, &n, sizeof(n), 0);
  n=ntohl(n);
 	
	printf("n= %d \n",n); 
    for (i = 0; i < n; i++) {
        scanf("%d", &arr1[i]);
	send(c,&arr1[i],sizeof(arr1[i]),0);
    }


        int k;
    recv(c, &k, sizeof(k), 0);



     printf("Asta e suma numerelor %d ", ntohl(k));
    


  close(c);
}
