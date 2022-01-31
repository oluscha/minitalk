SERVER = server
CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT = -L libft/ -lft

HEADERS = minitalk.h

SRC = 	server.c \
		client.c

OBJ = $(SRC:c=o)

all: $(SERVER) $(CLIENT)

server: server.o $(HEADERS)
		make -C libft
		$(CC) $(FLAGS) server.c $(LIBFT) -I. -o server

client: client.o $(HEADERS)
		make -C libft
		$(CC) $(FLAGS) client.c $(LIBFT) -I. -o client

clean:
	rm -f $(OBJ)
	make -C libft clean
	
fclean: clean
	rm -f libft/libft.a
	rm -f server
	rm -f client

re: fclean all

.PHONY: all libft clean fclean re