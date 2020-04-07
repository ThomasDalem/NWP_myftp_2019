##
## EPITECH PROJECT, 2020
## my_ftp
## File description:
## Makefile
##

CLIENTSRC	=	src/client/main.c		\
				src/client/client.c

SERVERSRC	=	src/server/main.c		\
				src/server/server.c		\

CLIENTOBJ	=	$(CLIENTSRC:.c=.o)

SERVEROBJ	=	$(SERVERSRC:.c=.o)

CLIENTNAME	=	client

SERVERNAME	=	server

CFLAGS		=	-Wall -Wextra -Werror

all: client server

client: $(CLIENTOBJ)
	gcc -o $(CLIENTNAME) $(CLIENTOBJ) $(CFLAGS)

server: $(SERVEROBJ)
	gcc -o $(SERVERNAME) $(SERVEROBJ) $(CFLAGS)

clean:
	rm -f $(CLIENTOBJ)
	rm -f $(SERVEROBJ)

fclean: clean
	rm -f $(CLIENTNAME)
	rm -f $(SERVERNAME)

re: fclean all
