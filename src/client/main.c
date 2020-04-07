/*
** EPITECH PROJECT, 2020
** my_ftp
** File description:
** client
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int ac, char **av)
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address;
    const int socklen = sizeof(address);
    char buffer[20];
    int port = atoi(av[1]);

    if (socket_fd == -1) {
        perror("socket");
        return (-1);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(port);
    if (connect(socket_fd, (struct sockaddr *)&address, sizeof(address))) {
        perror("connect");
        return (-1);
    }
    read(socket_fd, buffer, 20);
    printf("Server said: %s", buffer);
    close(socket_fd);
    return (0);
}
