# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vde-albu <vde-albu@student.42porto.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/27 14:12:14 by vde-albu          #+#    #+#              #
#    Updated: 2025/06/18 10:42:42 by vde-albu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -O$(OLEVEL) $(IFLAGS) \
	-D WINDOW_WIDTH=$(WINDOW_WIDTH) -D WINDOW_HEIGHT=$(WINDOW_HEIGHT)
IFLAGS = -I $(IDIR) -I $(LFTDIR)$(IDIR) -I $(MLXDIR)
SDIR = src/
IDIR = include/
ODIR = obj/
OBJ = main.o utils.o state.o map.o mlx.o image.o camera.o input.o overlay.o
OBJS = $(patsubst %, $(ODIR)%, $(OBJ))
LFTDIR = libft/
LFT = $(patsubst %, $(LFTDIR)%, libft.a)
MLXDIR = minilibx/
MLX = $(patsubst %, $(MLXDIR)%, libmlx.a)
MLXFLAGS = -lXext -lX11
OLEVEL = 0
WINDOW_WIDTH = 1600
WINDOW_HEIGHT = 900

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
	$(CC) $(CFLAGS) $(MLXFLAGS) -lm -o $@ $^

$(OBJS): $(ODIR)%.o: $(SDIR)%.c
	mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -o $@ -c $<

$(LFT):
	make -C $(LFTDIR)
