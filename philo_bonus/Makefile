SRCS = philo_bonus.c argument_check_bonus.c pthread_process_bonus.c thread_bonus.c
OBJS = ${SRCS:.c=.o}
NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

all: ${NAME}

bonus: ${NAME}

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
