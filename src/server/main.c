/*
** EPITECH PROJECT, 2020
** NWP_myftp_2019
** File description:
** main
*/

#include <stdio.h>
#include <stdlib.h>
#include "server.h"

int main(int ac, char **av)
{
    if (ac != 2) {
        fprintf(stderr, "Error: you must provide only 1 argument\n");
        printf("Usage: ./server [port]\n");
    }
    return (server(atoi(av[1])));
}
