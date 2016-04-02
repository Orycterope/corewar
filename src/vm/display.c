/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:32:37 by tvermeil          #+#    #+#             */
/*   Updated: 2016/04/01 22:33:26 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "arena.h"
#include "display.h"

void		init_display(t_arena *arena)
{
	initscr();
	start_color();
	cbreak();
	noecho();
	init_color(COLOR_WHITE, 400, 400, 400);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	arena->display = (t_display *)ft_memalloc(sizeof(t_display));
	arena->display->updates = NULL;
	arena->display->running = 0;
	arena->display->quitting = 0;
	arena->display->cps = 50;
	init_mem_display(arena);
	init_info_display(arena);
}

/*void		init_colors(t_arena *arena)
{
	t_player	*p;
	int			r;
	int			g;
	int			b;

	p = arena->players;
	while (p != NULL)
	{

		p = p->next;
	}
}*/

/*static void	print_color(t_mem_type t, unsigned char c, int y, int x)
{
	int	owner_color;
	//int	reader_color;
	short r;
	short g;
	short b;

	owner_color = t.owner % 6 + 1;
	//reader_color = t.reader % 6 + 1;
	color_content(owner_color, &r, &g, &b);
	init_color(owner_color,
		((double)r / 100 + ((double)t.w_turns / D_WRITE_TURNS * 2)) * 100,
		((double)r / 100 + ((double)t.w_turns / D_WRITE_TURNS * 2)) * 100,
		((double)r / 100 + ((double)t.w_turns / D_WRITE_TURNS * 2)) * 100);
	init_pair(owner_color, owner_color, 0);
	attron(COLOR_PAIR(owner_color));
	//mvwprintw(y, x, "%02x", c);
	attroff(COLOR_PAIR(owner_color));
	init_color(owner_color, r, g, b);
}*/

void		update_display(t_arena *arena)
{
	highlight_rw(arena);
	highlight_pcs(arena);
	update_infos(arena);
	wrefresh(arena->display->w_info);
	wrefresh(arena->display->w_mem);
	check_keystroke(arena);
}

void		destroy_display(t_arena *arena)
{
	delwin(arena->display->w_mem);
	delwin(arena->display->w_info);
	while (arena->display->updates != NULL)
		remove_update_struct(arena->display->updates, arena);
	free(arena->display);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	endwin();
}
