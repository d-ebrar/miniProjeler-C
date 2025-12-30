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
#define BUFFER_SIZE 2048

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

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
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

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("[LOG] Web Server listening on http://127.0.0.1:%d\n", PORT);

    while (keep_running) {

        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            if (errno == EINTR) break;
            perror("Accept failed");
            continue;
        }

        memset(buffer, 0, BUFFER_SIZE);

        int valread = read(new_socket, buffer, BUFFER_SIZE -1);

        if (valread < 0) {
            if (errno == EINTR) break;
            perror("Read failed");
            continue;
        }

        else if (valread == 0) {
            printf("[LOG] Client disconnected.\n");
            continue;
        }

        buffer[valread] = '\0';
        printf("[REQUEST] %s\n", buffer);

        char *body = "<!DOCTYPE html><html><body><h1>C Web Server</h1><p>Selam Sana Dünya!</p></body></html>";
        
        char header[BUFFER_SIZE];
        
        snprintf(header, sizeof(header),
                "HTTP/1.1 200 OK\r\n" 
                "Content-Type: text/html; charset=UTF-8\r\n"
                "Content-Length: %lu\r\n" 
                "Connection: close\r\n"
                "\r\n", strlen(body));

        send(new_socket, header, strlen(header), 0);
        send(new_socket, body, strlen(body), 0);

        close(new_socket);
        printf("[LOG] Connection closed.\n\n");
    }

    close(server_fd);
    printf("[LOG] Server closed gracefully.\n");
    
    return 0;
}

void handle_sigint(int sig) {
    keep_running = 0;
}