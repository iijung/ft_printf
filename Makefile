# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 03:49:45 by minjungk          #+#    #+#              #
#    Updated: 2022/07/27 09:02:29 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARFLAGS = rsc
CFLAGS = -Wall -Wextra -Werror -I. -I./Libft # -g3 -fsanitize=address

LIBFT = ./Libft/libft.a

NAME = libftprintf.a

SRCS = \
	ft_read.c \
	ft_parse.c \
	ft_write.c \
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


test: $(NAME)
	@$(CC) $(CFLAGS) -lftprintf -L. main.c
	@./a.out
	@rm a.out
