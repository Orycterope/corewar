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

void	init_display(t_arena *arena)
{
	int		i;

	initscr();
	start_color();
	cbreak();
	noecho();
	init_color(COLOR_WHITE, 400, 400, 400);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	arena->display = (t_display *)ft_memalloc(sizeof(t_display));
	arena->display->memory = (t_mem_type *)ft_memalloc(
		sizeof(t_mem_type) * MEM_SIZE);
	arena->display->running = 0;
	arena->display->quitting = 0;
	arena->display->cps = 50;
	arena->display->w_mem = newwin(MEM_SIZE / 64 + 1, 64 * 3 + 9 + 1, 5, 5); // no +1
	arena->display->w_info = newwin(20, 50, 10, 64 * 3 + 20);
	wtimeout(arena->display->w_info, 0);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != MEM_SIZE - 1)
			wprintw(arena->display->w_mem, "\n%0#6x : ", i);
		wprintw(arena->display->w_mem, "%02x ", (unsigned char)arena->memory[i]);
	}
	wrefresh(arena->display->w_mem);
}

static int	highlight_pcs(t_arena *arena)
{
	int			p_nbr;
	t_process	*p;

	p_nbr = 0;
	p = arena->processes;
	attron(A_BOLD);
	while (p != NULL)
	{
		attron(COLOR_PAIR(p->player * 10));
		mvprintw((int)(p->pc - arena->memory) / 64,
				((int)(p->pc - arena->memory) % 64) * 3 + 9,
				"%02x", (unsigned char)*(p->pc));
		attroff(COLOR_PAIR(p->player * 10));
		p_nbr++;
		p = p->next;
	}
	attroff(A_BOLD);
	move(MEM_SIZE / 64, 0);
	return (p_nbr);
}

static void	print_color(t_mem_type t, unsigned char c, int y, int x)
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
}

static void	highlight_rw(t_arena *arena)
{
	int			i;
	//int			player;
	//int			turns;
	t_mem_type	t;

	i = 0;
	move(0, 0);
	while (i < MEM_SIZE)
	{
		t = arena->display->memory[i];
		if (t.owner || t.reader)
		{
			print_color(t, (unsigned char)arena->memory[i],
				i / 64, (i % 64) * 3 + 9);
			if (t.w_turns)
				t.w_turns--;
			if (t.r_turns)
				t.r_turns--;
		}
		i++;
	}
}

void		check_keystroke(t_display *display)
{
	char	c;
	char	cont;

	cont = 1;
	while ((display->running == 0 && !display->quitting) || cont == 1)
	{
		cont = 0;
		c = wgetch(display->w_info);
		if (c == 's')
			break;
		else if (c == ' ')
			display->running = !display->running;
		else if (c == 'j')
			display->cps += (display->cps < 1000 ) ? 10 : 1000 - display->cps;
		else if (c == 'k')
			display->cps -= (display->cps >= 10 ) ? 10 : display->cps;
		else if (c == 'l')
			display->cps += (display->cps < 1000 ) ? 1 : 0;
		else if (c == ';')
			display->cps -= (display->cps > 0 ) ? 1 : 0;
		else if (c == 'q')
			display->quitting = 1;
	}
}

void		print_infos(t_arena *arena)
{
	t_display	*d;
	t_player	*player;
	t_process	*p;
	int			line;
	int			i;

	d = arena->display;
	p = arena->processes;
	i = 0;
	while (p != NULL)
	{
		i++;
		p = p->next;
	}
	mvwprintw(d->w_info, 0, 0,
			"Dumping memory at cycle %d (%d processus)", arena->cycle, i);
	mvwprintw(d->w_info, 3, 0, "Cycles per second : %4d", d->cps);
	line = 5;
	player = arena->players;
	while (player != NULL)
	{
		i = 0;
		p = arena->processes;
		while (p != NULL)
		{
			if (p->player == player->id)
				i++;
			p = p->next;
		}
		mvwprintw(d->w_info, line, 0, "Player %s :\n\tProcessus : %d\n\tLast live:  %d", player->name, i, player->last_live);
		line += 4;
		player = player->next;
	}
}

void		print_mem(t_arena *arena)
{
	int		p;

	highlight_rw(arena);
	p = highlight_pcs(arena);
	print_infos(arena);
	wrefresh(arena->display->w_info);
	wrefresh(arena->display->w_mem);
	check_keystroke(arena->display);
}

void	destroy_display(t_arena *arena)
{
	delwin(arena->display->w_mem);
	delwin(arena->display->w_info);
	free(arena->display->memory);
	free(arena->display);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	endwin();
}
