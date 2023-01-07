
NAME		=	philo
CC			=	cc
SRCS		=	$(wildcard *.c libs/*c)
OBJS		=	$(patsubst %.c, %.o, $(SRCS))
CFLAGS		=	-I./libs/include -Wall -Wextra -Werror
RM			=	rm -f

all:$(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re:fclean all

.PHONY: all clean fclean re