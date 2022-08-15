# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 03:49:45 by minjungk          #+#    #+#              #
#    Updated: 2022/08/15 19:35:37 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARFLAGS = rsc
CFLAGS = -Wall -Wextra -Werror -I. -I./Libft

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
	$(RM) $(OBJS)

fclean: clean
	$(MAKE) -C Libft fclean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus
