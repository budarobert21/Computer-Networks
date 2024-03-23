#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>

#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main() {
        int s;
        struct sockaddr_in server, client;
        int c, l, i;
        uint16_t a, b, suma;

        s = socket(AF_INET, SOCK_DGRAM, 0);
        if (s < 0)
        {
                printf("Eroare la crearea socketului server\n");
                return 1;
        }

        memset(&server, 0, sizeof(server));
        server.sin_port = htons(1234);
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;

        if (bind(s, (struct sockaddr *) &server, sizeof(server)) < 0)
        {
                printf("Eroare la bind\n");
                return 1;
        }

        l = sizeof(client);
        memset(&client, 0, sizeof(client));

        printf("Incepem primirea\n");

        while(1)
        {
                recvfrom(s, &a, sizeof(a), 0, (struct sockaddr *) &client, &l);
                recvfrom(s, &b, sizeof(b), 0, (struct sockaddr *) &client, &l);
                a = ntohs(a);
                b = ntohs(b);
                printf("Am primit a = %hu \n", a);
                printf("Am primit b = %hu \n", b);

                suma = a + b;
                suma = htons(suma);

                sendto(s, &suma, sizeof(suma), 0, (struct sockaddr *) &client, sizeof(client));
        }

        close(s);
}
