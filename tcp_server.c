#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8080
#define BUFFER_SIZE 1024

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};

    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) <= 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    printf("[LOG] Socket created successfully.\n");

    if (setsockopt(server_fd, SOL_SOCKET,
                   SO_REUSEADDR | SO_REUSEPORT, &opt,
                   sizeof(opt))) {
        perror("Setsockopt failed");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("[LOG] Bind to port %d successful.\n", PORT);

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("[LOG] Server listening on port %d...\n", PORT);

    printf("[LOG] Waiting for connections...\n");

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }
    printf("[LOG] Connection accepted!\n");

    while (keep_running) {
        memset(buffer, 0, BUFFER_SIZE);

        int valread = read(new_socket, buffer, BUFFER_SIZE -1);

        if (valread < 0) {
            if (errno == EINTR) break;
            perror("Read failed");
            break;
        }

        else if (valread == 0) {
            printf("[LOG] Client disconnected.\n");
            break;
        }

        buffer[valread] = '\0';
        printf("Client Sent: %s\n", buffer);

        int i;
        for (i = 0; i < valread; i++) {
            buffer[i] = toupper((unsigned char)buffer[i]);
        }

        if (strstr(buffer, "EXIT") != NULL) {
            printf("[LOG] Shutdown command received. Breaking loop...\n");
            break;
        }
        
        if (send(new_socket, buffer, strlen(buffer), 0) <= 0) {
            printf("[LOG] Send failed.\n");
            break;
        }
    }

    close(new_socket);
    close(server_fd);

    printf("[LOG] Server closed gracefully.\n");
    
    return 0;
}

void handle_sigint(int sig) {
    keep_running = 0;
}