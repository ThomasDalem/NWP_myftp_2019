/*
** EPITECH PROJECT, 2020
** my_ftp
** File description:
** server
*/

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int setSocket(struct sockaddr_in *addr, int port)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_fd == -1) {
        perror("socket");
        return (-1);
    }
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    addr->sin_addr.s_addr = INADDR_ANY;
    if (bind(socket_fd, (struct sockaddr *)addr, sizeof(*addr)) == -1) {
        perror("bind");
        return (-1);
    }
    return (socket_fd);
}

int add_child_socket_to_set(fd_set *readfds, int *clients_sockets, int max_fd)
{
    int fd = 0;

    for (int i = 0; i < 10; i++) {
        fd = clients_sockets[i];
        if (fd > 0) {
            FD_SET(fd, readfds);
        }
        if (fd > max_fd) {
            return (fd);
        }
    }
    return (max_fd);
}

void addConnection(int *clients_fd, int server_fd)
{
    struct sockaddr_in addr;
    socklen_t socklen = sizeof(addr);
    int i = 0;
    char buffer[20] = "Hello world!\n";

    for (; i < 10; i++) {
        if (clients_fd[i] == 0) {
            clients_fd[i] = accept(server_fd, (struct sockaddr *)&addr, &socklen);
            break;
        }
    }
    if (clients_fd[i] == -1) {
        perror("accept");
    }
    printf("New connection: %s", inet_ntoa(addr.sin_addr));
    printf(":%d\n", ntohs(addr.sin_port));
    write(clients_fd[i], buffer, sizeof(buffer));
    close(clients_fd[i]);
    clients_fd[i] = 0;
}

int server_loop(int server_fd)
{
    int client = 0;
    int clients_fd[10] = {0};
    fd_set readfds;
    int max_fd = server_fd;

    while (1) {
        FD_ZERO(&readfds);
        FD_SET(server_fd, &readfds);
        max_fd = add_child_socket_to_set(&readfds, clients_fd, max_fd);
        if (select(max_fd + 1, &readfds, NULL, NULL, NULL) == -1) {
            perror("select");
        }
        if (FD_ISSET(server_fd, &readfds)) {
            addConnection(clients_fd, server_fd);
        }
        close(client);
    }
}

int server(int port)
{
    int socket_fd = 0;
    struct sockaddr_in address = {0};

    socket_fd = setSocket(&address, port);
    if (socket_fd == -1) {
        return (-1);
    }
    if (listen(socket_fd, 10) == -1) {
        perror("listen");
        return (-1);
    }
    server_loop(socket_fd);
    close(socket_fd);
    return (0);
}