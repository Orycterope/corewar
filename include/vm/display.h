/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:08:20 by tvermeil          #+#    #+#             */
/*   Updated: 2016/04/01 21:58:17 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# define D_READ 1
# define D_WRITE 2
# define D_READ_TURNS 4
# define D_WRITE_TURNS 6
# include <ncurses.h>

typedef struct	s_mem_type
{
	char		owner;
	char		reader;
	char		r_turns;
	char		w_turns;
}				t_mem_type;

typedef struct	s_display
{
	t_mem_type	*memory;
	int			running;
	int			cps;
	int			quitting;
	WINDOW		*w_mem;
	WINDOW		*w_info;
}				t_display;

void		init_display();
void		destroy_display(t_arena *arena);
void		print_mem(t_arena *arena);

#endif
