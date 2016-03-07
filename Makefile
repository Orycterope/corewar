# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/18 19:13:31 by tvermeil          #+#    #+#              #
#    Updated: 2016/03/07 17:59:49 by tvermeil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#MAKEFLAGS += --no-print-directory

all: libft.a asm vm

libft.a:
	@make -C libft all

asm:
	@make -C src/asm all

vm:
	@make -C src/vm all

clean:
	@make -C libft clean
	@make -C src/asm clean
	@make -C src/vm clean
	@rmdir obj 2> /dev/null || true

fclean: clean
	@make -C libft fclean
	@make -C src/asm fclean
	@make -C src/vm fclean

re: fclean all

ac: all clean

norme:
	norminette $(LIBFT_SRC) $(SRC) include/*.h

.PHONY: all clean fclean re
