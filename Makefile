
NAME		=	philo
CC			=	cc
SRCS		=	$(wildcard *.c libs/*c)
OBJS		=	$(patsubst %.c, %.o, $(SRCS))
CFLAGS		=	-I./libs/include -fsanitize=address #-Wall -Wextra -Werror 
RM			=	rm -f

all:$(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(RM) $(OBJS) 

fclean: clean
	$(RM) $(NAME)

re:fclean all

.PHONY: all clean fclean re