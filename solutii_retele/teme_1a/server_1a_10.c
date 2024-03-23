		//Un client trimite unui server doua siruri de c/ pozitii identice in cele doua siruri si cu numarul de aparitii ale acestui caracter.
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
    int len1,len2;
        char sir1[MAX_SIZE];
        char sir2[MAX_SIZE];
    c = accept(s, (struct sockaddr *) &client, &l);
    printf("S-a conectat un client.\n");
    // deservirea clientului

    recv(c, &len1, sizeof(len1), MSG_WAITALL);
        len1=ntohl(len1);
    printf("primit lungimea listei %d \n",len1);

    recv(c,&sir1,len1*sizeof(char),MSG_WAITALL);


printf("citit sirul 1: %s\n",sir1);


        recv(c, &len2, sizeof(len1), MSG_WAITALL);
        len2=ntohl(len2);
    printf("primit lungimea listei %d \n",len2);

    recv(c,&sir2,len2*sizeof(char),MSG_WAITALL);

printf("citit sirul 2: %s\n",sir2);
    char caracter_aux;
    char caracter;
        int numar_aparitii=0;
        if(len1<len2)
        {
        for(int i=0;i<len1;i++)
        {
                int nr_aparitii_aux=0;
                caracter_aux=sir1[i];
		printf("%c\n",caracter_aux);
        for(int i=0;i<len1;i++)
                {
 printf("%c si %c",sir1[i],sir2[i]);
                if(sir1[i]==sir2[i]&&caracter_aux==sir2[i]){
                        nr_aparitii_aux++;
			printf("%c si %c\n",sir1[i],sir2[i]);}
			
                }
                        if(nr_aparitii_aux>numar_aparitii){
                                numar_aparitii=nr_aparitii_aux;
                                caracter=caracter_aux;

                                }
                }

                }
else{
 for(int i=0;i<len2;i++)
        {
                int nr_aparitii_aux=0;
                caracter_aux=sir2[i];
		printf("%c\n",caracter_aux);
        for(int i=0;i<len2;i++)
                {
			 printf("%c si %c\n",sir1[i],sir2[i]);
                if(sir1[i]==sir2[i]&&caracter_aux==sir2[i]){
                        nr_aparitii_aux++;
			 printf("%c si %c",sir1[i],sir2[i]);}
                }
                        if(nr_aparitii_aux>numar_aparitii){
                                numar_aparitii=nr_aparitii_aux;
                                caracter=caracter_aux;
				printf("a");
                                }
                }




}
                printf("caracterul este: %c\n",caracter);
                printf("numar aparitii: %d\n",numar_aparitii);
                numar_aparitii=htonl(numar_aparitii);
                send(c,&caracter,sizeof(caracter),0);
                send(c,&numar_aparitii,sizeof(int),0);


         printf("Trimis elemente\n");

    close(c);
    // sfarsitul deservirii clientului;
}  }
       
