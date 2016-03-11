# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/18 19:13:31 by tvermeil          #+#    #+#              #
#    Updated: 2016/03/11 21:40:34 by tvermeil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = asm

SRC_PATH = .
ROOT = ../..
OBJ_FOLDER = obj/$(NAME)
INC_PATH = $(ROOT)/include/$(NAME) \
		   $(ROOT)/include/libft \

OBJ_PATH = $(ROOT)/$(OBJ_FOLDER)
DST_PATH = $(ROOT)
LFT_PATH = $(ROOT)

CC = gcc
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I ,$(INC_PATH))
LDFLAGS = -L$(LFT_PATH)
LDLIBS = -lft

SRC_NAME = asm.c \
		   error.c \
		   instruc_list_fct.c \
		   label_list_fct.c \
		   parser.c \

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

r: fclean f

fast:
	@printf "\e[1;32m _.----==# FAST MODE #==----._\033[0m\n\n"
	@make -j
	@printf "\e[1;32m _____________________________\033[0m\n"

f: fast

n:
	norminette $(SRC) ../../include/asm/*.h | grep --color -E '^|Norme.*$$'

enum:
	@ls *.c | sed 's/^\(.\)/       \1/g' | sed 's/\(.\)$$/\1 \\/g'

enum_func:
	@if [ ! -z "$(file)" ]; then \
		echo "$$(grep -i '^[a-z].*' $(file) | sed 's/)/);/g')"; \
		else \
		echo "make enum_func file='<file>'"; \
		fi ;

enum_all_func:
	@grep -i '^[a-z].*' $(SRC) | sed 's/\(^.*\.c:\)/\1\#/g' | tr \# '\n' | sed 's/)/);/g' | grep --color -E '^|^.*:'

create_gitignore:
	@echo ".*" > .gitignore

add_gitignore:
	@if [ ! -z "$(add)" ]; then \
		echo "$(add)" >> .gitignore ; \
		else \
		echo "make add_gitignore add='<add>'"; \
		fi ;

gitignore:
	@cat .gitignore

create_git:
	@if [ ! -z "$(url)" ]; then \
		git clone "$(url)" tmp_a0168aeb65b146a38ece5d8379b5811a6f53d00bb7730af7c40917c2f6b7224a060dcd1ad763bda0; \
		mv tmp_a0168aeb65b146a38ece5d8379b5811a6f53d00bb7730af7c40917c2f6b7224a060dcd1ad763bda0/.git ./; \
		rm -rf tmp_a0168aeb65b146a38ece5d8379b5811a6f53d00bb7730af7c40917c2f6b7224a060dcd1ad763bda0; \
		else \
		echo "make create_git url='<url>'"; \
		fi ;

git_url:
	@echo "$$(git --git-dir=.git config --get remote.origin.url)"

check_clone:
	git clone "$$(git --git-dir=.git config --get remote.origin.url)" check_clone

.PHONY: all clean fclean re
