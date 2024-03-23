#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
 
int main() {
  int c;
  struct sockaddr_in server;
  uint16_t a, b, suma, i, k;
  
  
  c = socket(AF_INET, SOCK_DGRAM, 0);
  if (c < 0) {
    printf("Eroare la crearea socketului client\n");
    return 1;
  }
  
  memset(&server, 0, sizeof(server));
  server.sin_port = htons(53293);
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr("127.0.0.1");
  
  for (i = 0; i < 10000; i++) {
    k = i + 1;
    k = htons(k);
    sendto(c, &k, sizeof(k), 0, (struct sockaddr *) &server, sizeof(server));
  }
  
  close(c);
}
