# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 03:49:45 by minjungk          #+#    #+#              #
#    Updated: 2022/08/07 02:25:06 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARFLAGS = rsc
CFLAGS = -Wall -Wextra -Werror -I. -I./Libft  -g3 # -fsanitize=address

LIBFT = ./Libft/libft.a

NAME = libftprintf.a

SRCS = \
	ft_make_token.c \
	ft_parse_token.c \
	ft_printf.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)
bonus: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C Libft
	cp $(LIBFT) $@
	$(AR) $(ARFLAGS) $@ $^ 

clean:
	$(MAKE) -C Libft clean
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(MAKE) -C Libft fclean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus


LD_FLAGS = -I./Libft -L. -lftprintf
test: $(NAME)
	@$(RM) a.out
	$(CC) $(CFLAGS) main.c $(LD_FLAGS)
#	$(CC) main.c $(LD_FLAGS)
	@./a.out | cat -e

