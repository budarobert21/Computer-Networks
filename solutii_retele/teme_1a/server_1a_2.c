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
    int len;
	char sir[MAX_SIZE];
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului

    recv(c, &len, sizeof(len), MSG_WAITALL);
        len=ntohl(len);
    printf("primit lungimea listei %d \n",len);
   
    recv(c,&sir,len*sizeof(char),MSG_WAITALL);    
    
printf("citit sirul\n");
     int cnt=0;
	 for(int i=0;i<len;i++){
		if(sir[i]==' ')
			cnt++;
	 }
	 cnt=htonl(cnt);
	 send(c,&cnt,sizeof(int),0);
	 printf("Trimis numarul de spatii\n");
	 
    close(c);
    // sfarsitul deservirii clientului;
  }
}
