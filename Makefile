# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 03:49:45 by minjungk          #+#    #+#              #
#    Updated: 2022/07/17 12:47:47 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ARFLAGS = rsc
CFLAGS = -Wall -Wextra -Werror -I. -I./libft

LIBFT = ./libft/libft.a

NAME = libftprintf.a

SRCS = \
	ft_printf.c

SRCS_B = 

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C libft
	cp $(LIBFT) $@
	$(AR) $(ARFLAGS) $@ $^ 

bonus: 
	$(MAKE) OBJS=$(OBJS_B) all 

clean:
	$(MAKE) -C libft clean
	$(RM) $(OBJS) $(OBJS_B)

fclean: clean
	$(MAKE) -C libft fclean
	$(RM) $(NAME)

re: fclean
	$(MAKE) all

.PHONY: all clean fclean re bonus


test: $(NAME)
	@$(CC) $(CFLAGS) -lftprintf -L. main.c
	@./a.out
	@rm a.out
