# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 14:12:14 by vde-albu          #+#    #+#              #
#    Updated: 2025/05/27 14:22:42 by vde-albu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -g -I $(IDIR) -I $(LFTDIR)$(IDIR) -I $(MLXDIR)
SDIR = src/
IDIR = include/
ODIR = obj/
OBJ = fdf.o
OBJS = $(patsubst %, $(ODIR)%, $(OBJ))
LFTDIR = libft/
LFT = $(patsubst %, $(LFTDIR)%, libft.a)
MLXDIR = minilibx/
MLX = $(patsubst %, $(MLXDIR)%, libmlx.a)

.PHONY: all clean fclean re

all: $(NAME)

clean:
	rm -fr $(ODIR)
	make $@ -C $(LFTDIR)

fclean: clean
	rm -fr $(NAME)
	make $@ -C $(LFTDIR)

re: fclean all

$(NAME): $(OBJS) $(LFT) $(MLX)
	$(CC) $(CFLAGS) -lXext -lX11 -o $@ $^

$(OBJS): $(ODIR)%.o: $(SDIR)%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LFT):
	make -C $(LFTDIR)
