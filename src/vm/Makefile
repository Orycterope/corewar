# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/18 19:13:31 by tvermeil          #+#    #+#              #
#    Updated: 2016/05/08 16:00:39 by tvermeil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar

SRC_PATH = .
ROOT = ../..
OBJ_FOLDER = obj/vm
INC_PATH = $(ROOT)/include/vm \
		   $(ROOT)/include/libft \

OBJ_PATH = $(ROOT)/$(OBJ_FOLDER)
DST_PATH = $(ROOT)
LFT_PATH = $(ROOT)

CC = gcc -g
CFLAGS = -Wall -Wextra #-Werror
CPPFLAGS = $(addprefix -I ,$(INC_PATH))
LDFLAGS = -L$(LFT_PATH)
LDLIBS = -lft -lncurses

SRC_NAME =	arena.c \
			player.c \
			process.c \
			get_input.c \
			get_player_code.c \
			main.c \
			op.c \
			instruction_param.c \
			instructions_p1.c \
			instructions_p2.c \
			instructions_p3.c \
			instructions_p4.c \
			execution.c \
			read_write.c \
			display.c \
			display_infos.c \
			display_mem.c \
			display_color.c \

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
DST = $(addprefix $(DST_PATH)/,$(NAME))

all: $(ROOT)/libft.a $(DST)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo -n .

$(DST): $(OBJ)
	@$(CC) $(OBJ) $(LDFLAGS) $(LDLIBS) -o $(DST)
	@echo " . \033[32m$(NAME)\033[0m done"
	@echo [Warning] no compilation flag used

$(ROOT)/libft.a:
	@make -C $(ROOT) libft.a
clean:
	@-cd $(ROOT) && rm -fv $(addprefix $(OBJ_FOLDER)/,$(OBJ_NAME))
	@rmdir $(OBJ_PATH) $(ROOT)/obj 2> /dev/null || true

fclean: clean
	@-cd $(DST_PATH) && rm -fv $(NAME)

re: fclean all

ac: all clean

norme:
	@norminette $(SRC)

.PHONY: all clean fclean re
