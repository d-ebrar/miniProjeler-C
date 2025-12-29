#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main()
{
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = { 0 };
    char input[BUFFER_SIZE];

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Socket creation failed");
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("Invalid address/Address not supported \n");
        return -1;
    }

    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        printf("Connection Failed");
        return -1;
    }
    printf("[LOG] Connected to server on port %d\n", PORT);

    while (1) {
        printf("Enter your message (Type 'EXIT' to quit): ");
        fgets(input, BUFFER_SIZE, stdin);
        
        input[strcspn(input, "\n")] = 0;

        send(client_fd, input, strlen(input), 0);

        if (strcasecmp(input, "EXIT") == 0) {
            printf("[LOG] Exiting...\n");
            break;
        }

        memset(buffer, 0, BUFFER_SIZE);

        int valread = read(client_fd, buffer, BUFFER_SIZE - 1);

        if (valread > 0) {
            buffer[valread] = '\0';
            printf("[SERVER]: %s\n", buffer);
        }
        else {
            printf("[LOG] Server connection lost.\n");
            break;
        }
    }

    close(client_fd);

    return 0;
}