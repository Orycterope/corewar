# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/12/18 19:13:31 by tvermeil          #+#    #+#              #
#    Updated: 2016/05/08 22:22:10 by tvermeil         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS += --no-print-directory

SUB_MAKEFILES = libft \
				src/asm \
				src/vm \

all:
	@make -C libft all
	@make -C src/vm all
	@make -C src/asm all

libft.a:
	@make -C libft all

asm:
	@make -C src/asm all

corewar:
	@make -C src/vm all

clean:
	@-for i in $(SUB_MAKEFILES) ; do \
		make -C $$i clean; \
	done
	@rmdir obj 2> /dev/null || true

fclean: clean
	@for i in $(SUB_MAKEFILES) ; do \
		make -C $$i fclean; \
	done

re: fclean all

ac: all clean

norme:
	@for i in $(SUB_MAKEFILES) ; do \
		make -C $$i norme; \
	done
	@norminette include/*.h

.PHONY: all clean fclean re
