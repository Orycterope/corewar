/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:32:37 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 16:29:20 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "arena.h"
#include "display.h"

static void	attribute_src_code(t_arena *arena)
{
	t_player		*p;
	unsigned int	size;
	unsigned int	begin;

	p = arena->players;
	while (p != NULL)
	{
		wattron(arena->display->w_bkp, COLOR_PAIR(
			p->id * 10 + MAX_PLAYERS + 2));
		size = 0;
		begin = p->begin - arena->memory;
		while (size < p->champ_size)
		{
			mvwprintw(arena->display->w_bkp,
					(begin + size) / 64,
					((begin + size) % 64) * 3 + 9,
					"%02x ", (unsigned char)arena->memory[begin + size]);
			arena->display->owner_tab[begin + size++] = (char)p->id;
		}
		wattroff(arena->display->w_bkp, COLOR_PAIR(
			p->id * 10 + MAX_PLAYERS + 2));
		p = p->next;
	}
}

void		init_display(t_arena *arena)
{
	initscr();
	start_color();
	cbreak();
	noecho();
	init_color(COLOR_WHITE, 400, 400, 400);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	init_colors(arena->players);
	arena->display = (t_display *)ft_memalloc(sizeof(t_display));
	arena->display->updates = NULL;
	arena->display->running = 0;
	arena->display->quitting = 0;
	arena->display->cps = 50;
	init_mem_display(arena);
	attribute_src_code(arena);
	init_info_display(arena);
}

void		update_display(t_arena *arena)
{
	highlight_rw(arena);
	highlight_pcs(arena);
	overwrite(arena->display->w_bkp, arena->display->w_mem);
	overlay(arena->display->w_pcs, arena->display->w_mem);
	wrefresh(arena->display->w_mem);
	regulate_speed(arena);
}

void		destroy_display(t_arena *arena)
{
	delwin(arena->display->w_mem);
	delwin(arena->display->w_info);
	delwin(arena->display->w_bkp);
	while (arena->display->updates != NULL)
		remove_update_struct(arena->display->updates, arena);
	free(arena->display);
	init_color(COLOR_WHITE, 800, 800, 800);
	endwin();
}
