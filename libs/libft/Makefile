NAME		=	libft.a
CC			=	cc
ALL_SRCS	=	$(wildcard *.c)
BONUS_SRCS	=	$(wildcard ft_lst*.c)
SRCS		=	$(filter-out $(BONUS_SRCS), $(ALL_SRCS))
OBJS		=	$(patsubst %.c, %.o, $(SRCS))
BONUS_OBJS	=	$(patsubst %.c, %.o, $(BONUS_SRCS))
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f
AR			=	ar rcs

%.o:%.c
	$(CC) $(CFLAGS) -c $< -o $@

all:$(NAME)

$(NAME):$(OBJS)
	$(AR) $(NAME) $(OBJS)

bonus: $(NAME) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean:clean
	$(RM) $(NAME)

re:fclean all

.PHONY: all clean bonus fclean re
