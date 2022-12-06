# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 03:49:45 by minjungk          #+#    #+#              #
#    Updated: 2022/12/06 22:58:13 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_ON_ERROR:
.DEFAULT_GOAL := all

LIBFT = ./libft/libft.a
$(LIBFT):
	$(MAKE) -C $(@D) bonus

CFLAGS		= -Wall -Wextra -Werror -MMD -MP -O3
CPPFLAGS	= -I$(dir $(LIBFT))
ARFLAGS		= rsc

NAME = libftprintf.a

SRCS = \
	ft_utoa.c \
	ft_make_token.c \
	ft_parse_token.c \
	ft_printf.c

OBJS = $(SRCS:.c=.o)
DEPS = $(SRCS:.c=.d)
-include $(DEPS)

all bonus: $(NAME)

$(NAME): $(OBJS) | $(LIBFT)
	cp $(LIBFT) $@
	$(AR) $(ARFLAGS) $@ $^ 

clean:
	$(MAKE) -C $(dir $(LIBFT)) clean
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(MAKE) -C $(dir $(LIBFT)) fclean
	$(RM) $(NAME)

re: fclean
	$(MAKE) $(if $(filter bonus, $(MAKECMDGOALS)), bonus, all)

.PHONY: all clean fclean re bonus
