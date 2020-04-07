/*
** EPITECH PROJECT, 2020
** my_ftp
** File description:
** client
*/

#include <stdio.h>
#include <stdlib.h>
#include "client.h"

int main(int ac, char **av)
{
    if (ac != 2) {
        fprintf(stderr, "Error: you must provide only 1 argument\n");
        printf("Usage: ./client [port]\n");
        return (-1);
    }
    return (client(atoi(av[1])));
}
