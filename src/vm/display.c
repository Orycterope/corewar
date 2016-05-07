/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:32:37 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/07 18:23:23 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "arena.h"
#include "display.h"

static void	attribute_src_code(t_arena *arena);

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

void		init_pairs(int players)
{
	int		o;
	int		oi;

	o = 0;
	while (++o <= players)
	{
		oi = -1;
		while (++oi < D_WRITE_TURNS + 1)
		{
			init_pair(10 * o + oi + MAX_PLAYERS + 1,
						100 + o * 10 + D_WRITE_TURNS - oi,
						0);
		}
	}
}

void		init_colors(t_player *p) // p = first player
{
	float		i;
	short		r;
	short		g;
	short		b;
	int			c;

	c = 0;
	while (p != NULL)
	{
		color_content(p->id, &r, &g, &b);
		i = 11;
		while (--i > 0)
			init_color(
					100 + p->id * 10 + 9 - i, // 9 - i
					//r * i / 10,// + (r + g + b) / 3 * (i - 5) / 10,
					//g * i / 10,// + (r + g + b) / 3 * (i - 5) / 10,
				   	//b * i / 10);// + (r + g + b) / 3 * (i - 5) / 10);
				///	r * 1.0 * (i - 10) + (((r + g + b) / 3 - r) + 0) * (i) / 10,
				///	g * 1.0 * (i - 10) + (((r + g + b) / 3 - g) + 0) * (i) / 10,
				///   	b * 1.0 * (i - 10) + (((r + g + b) / 3 - b) + 0) * (i) / 10);
					r + (((r + g + b) / 3 - r) + 400) * (i) / 25,
					g + (((r + g + b) / 3 - g) + 800) * (i) / 25,
					b + (((r + g + b) / 3 - b) + 700) * (i) / 25);
		init_pair(p->id, p->id, COLOR_BLACK);
		c++;
		p = p->next;
	}
	init_pairs(c);
}

void		update_display(t_arena *arena)
{
	highlight_rw(arena);
	highlight_pcs(arena);
	//update_infos(arena);
	overwrite(arena->display->w_bkp, arena->display->w_mem);
	overlay(arena->display->w_pcs, arena->display->w_mem);
	wrefresh(arena->display->w_mem);
	check_keystroke(arena);
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
