NAME = libftprintf.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror 

SRCS = $(wildcard *.c)

OBJS = $(patsubst %.c, %.o, $(SRCS))

AR = ar rcs

RM = rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	 $(AR) $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
