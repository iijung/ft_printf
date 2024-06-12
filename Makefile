# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minjungk <minjungk@student.42seoul.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/17 03:49:45 by minjungk          #+#    #+#              #
#    Updated: 2024/06/13 02:57:42 by minjungk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DELETE_ON_ERROR:
.DEFAULT_GOAL := all

# **************************************************************************** #
# depdency
# **************************************************************************** #

LIBFT = ./libft/libft.a

CPPFLAGS	+= -I$(dir $(LIBFT))

$(LIBFT):
	@if [ ! -f $(@D)/Makefile ]; then git submodule update --init; fi
	$(MAKE) -C $(@D) bonus

# **************************************************************************** #
# main
# **************************************************************************** #

NAME = libftprintf.a

CFLAGS		+= -Wall -Wextra -Werror -O3
CPPFLAGS	+= -MMD -MP
ARFLAGS		= rsc

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

# **************************************************************************** #
# for test
# **************************************************************************** #

LIBS = $(NAME)

CPPFLAGS	+= $(foreach dir, $(dir $(LIBS)), -I$(dir))
LDFLAGS 	+= $(foreach dir, $(dir $(LIBS)), -L$(dir))
LDLIBS  	+= $(foreach lib, $(notdir $(LIBS)), -l$(patsubst lib%.a,%,$(lib)))
