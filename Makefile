# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jubarbie <jubarbie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/10/30 16:51:35 by jubarbie          #+#    #+#              #
#    Updated: 2016/09/18 23:03:36 by jubarbie         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS= -ILibs/libft -ILibs/libmlx -IIncludes -Wall -Wextra -Werror
SRC=	Sources/wolf3d.c		\
		Sources/options.c		\
		Sources/env.c			\
		Sources/map.c			\
		Sources/textures.c		\
		Sources/vector.c		\
		Sources/error.c			\
		Sources/key_event.c		\
		Sources/moves.c			\
		Sources/color_hsv.c		\
		Sources/menu.c			\
		Sources/light.c			\
		Sources/raycast.c		\
		Sources/raycast2.c		\
		Sources/raycast_floor.c		
OBJ=$(SRC:.c=.o)
NAME=wolf3d

$(NAME): $(OBJ)
	@make -C Libs/libft
	@make -C Libs/libmlx
	@$(CC) -LLibs/libft/ -lft -LLibs/libmlx/ -lmlx -framework OpenGL -framework AppKit -framework Opencl -o $@ $^
	@echo "\033[32m[OK]\033[0m wolf3d created"

all: $(NAME)
	
%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@make clean -C Libs/libft
	@rm -rf $(OBJ)
	@echo "\033[32m[OK]\033[0m object files deleted"

fclean: clean
	@make fclean -C Libs/libft
	@make clean -C Libs/libmlx
	@rm -rf $(NAME)
	@echo "\033[32m[OK]\033[0m wolf3d deleted"

re: fclean all
