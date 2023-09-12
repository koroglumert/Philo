SRCS = philo.c argument_check.c pthread_process.c thread.c utils.c
OBJS = ${SRCS:.c=.o}
NAME = philo
CC = gcc
CFLAGS = -Wall -Wextra -Werror  -fsanitize=thread -g
RM = rm -rf

all: ${NAME}

${NAME}: ${OBJS}
	@${CC} ${CFLAGS} ${OBJS} -o ${NAME} 

%.o: %.c
	@$(CC) $(CFLAGS) -Imlx -c $< -o $@ 

clean:
	@${RM} ${OBJS}

fclean: clean
	@${RM} ${NAME}

re: fclean all

.PHONEY: all clean fclean re
