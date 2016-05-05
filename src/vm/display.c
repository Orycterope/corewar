/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:32:37 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/05 18:32:15 by tvermeil         ###   ########.fr       */
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
	attribute_src_code(arena);
	init_mem_display(arena);
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
		size = 0;
		begin = p->begin - arena->memory;
		while (size < p->champ_size)
			arena->display->owner_tab[begin + size++] = (char)p->id;
		p = p->next;
	}
}

void		init_pairs(int players)
{
	int		o;
	int		r;
	int		oi;
	int		ri;

	o = -1;
	while (++o < players)
	{
		oi = -1;
		while (++oi < D_WRITE_TURNS)
		{
			r = -1;
			while (++r < players)
			{
				ri = -1;
				while (++ri < D_READ_TURNS)
				{
					init_pair(o * 1000 + oi * 100 + r * 10 + ri + 10,
							100 + o * 10 + oi,
						   	100 + r * 10 + ri);
				}
			}
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
		i = 8;
		while (--i >= 0)
			init_color(100 + p->id * 10 + i, r * i / 7, g * i / 7, b * i / 7);
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
