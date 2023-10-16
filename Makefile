# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yorlians <yorlians@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 16:44:25 by bluzi             #+#    #+#              #
#    Updated: 2023/09/29 20:50:37 by yorlians         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

NAME		= cub3D

CFLAGS		:= 	-Wextra -Wall -Werror
LIBMLX		=	lib/MLX42

BLUE		=	\033[0;94m
GREEN		=	\033[0;32m
PURPLE		=	\033[0;35m
RESET		=	\033[0m

HEADERS		=	-I include -I $(LIBMLX)/include
AAA 		=	$(LIBMLX)/build/libmlx42.a
LIBS		=	$(AAA) -ldl -lglfw -pthread -lm

SRCS		=	src/main.c								\
				src/hooks.c								\
				src/color.c								\
				src/check.c								\
				src/utils.c								\
				src/parser.c							\
				src/sprite.c							\
				src/texture.c							\
				src/painter.c							\
				src/minimap.c							\
				src/utils_2.c							\
				src/utils_3.c							\
				src/ray_cast.c							\
				src/free_all.c							\
				src/movement.c							\
				src/id_checks.c							\
				src/color_utils.c						\
				src/parser_utils.c						\
				src/get_next_line/get_next_line.c		\
				src/get_next_line/get_next_line_utils.c

OBJS		=	${SRCS:.c=.o}

all:			$(AAA) $(NAME)
				@printf "\n"
				@printf "$(PURPLE) ______    _    _    _____     _____    ____ \n$(RESET)"
				@printf "$(PURPLE)|  ____|  | |  | |  | |  \ \  |____ \  |  _  \ \n$(RESET)"
				@printf "$(PURPLE)| |       | |  | |  | |_ / /      / /  | |  \ \ \n$(RESET)"
				@printf "$(PURPLE)| |       | |  | |  | |  \ \      \ \  | |   | | \n$(RESET)"
				@printf "$(PURPLE)| |____   | |__| |  | |__| |   ____| | | |__/ / \n$(RESET)"
				@printf "$(PURPLE)|______|  |______|  |______/  |_____/  |_____/ \n$(RESET)"
				@printf "$(PURPLE)                                                     \n$(RESET)"
				@printf "\n"

$(AAA):
				@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: 		%.c
				@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): 		$(OBJS)
				@$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)
				echo "$(GREEN)✅🚀 Program compiled successfully 🚀✅$(RESET)"

clean:
				@rm -f $(OBJS)
				echo "$(BLUE)✨🧹🧺✨ Removed object files ✨🧺🧹✨$(RESET)"

fclean: 		clean
				@rm -f $(NAME)
				@rm -rf $(LIBMLX)/build
				echo "$(BLUE)✨💦🛁✨ Removed executable ✨🛁💦✨$(RESET)"

re: 			clean all

bonus : fclean all

.PHONY:			all, clean, fclean, re, libmlx, libft, bonus