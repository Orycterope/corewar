/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:32:37 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/30 23:48:33 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "arena.h"
#include "display.h"

void	init_display(t_arena *arena)
{
	//t_player	*p;
	//int			color;

	initscr();
	start_color();
	cbreak();
	noecho();
	init_color(COLOR_WHITE, 400, 400, 400);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	/*p = arena->players;
	color = 0;
	while (p != NULL)
	{
		init_pair(p->id * 10 + 0, color % 6 + 1, 0);
		init_pair(p->id * 10 + 1, color % 6 + 1, 0);
		init_pair(p->id * 10 + 2, color % 6 + 1, 0);
		color++;
		p = p->next;
	}*/
	arena->display = (t_display *)ft_memalloc(sizeof(t_display));
	arena->display->memory = (t_mem_type *)ft_memalloc(
		sizeof(t_mem_type) * MEM_SIZE);
	arena->display->running = 0;
	arena->display->cps = 50;
}

static int	highlight_pcs(t_arena *arena)
{
	int			p_nbr;
	t_process	*p;

	p_nbr = 0;
	p = arena->processes;
	//start_color();
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
		r / 100 * (t.w_turns + 2),
		g / 100 * (t.w_turns + 2),
		b / 100 * (t.w_turns + 2));
	init_pair(owner_color, owner_color, 0);
	attron(COLOR_PAIR(owner_color));
	mvprintw(y, x, "%02x", c);
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

void		print_mem(t_arena *arena)
{
	int		i;

	move(0,0);
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != MEM_SIZE - 1)
		{
			if (i != 0)
				addch('\n');
			printw("%0#6x : ", i);
		}
		printw("%02x", (unsigned char)arena->memory[i]);
		printw(" ");
		i++;
	}
	highlight_rw(arena);
	printw("Dumping memory at cycle %d (%d processus):", arena->cycle, highlight_pcs(arena));
	refresh();
	getch();
}

void	destroy_display(t_arena *arena)
{
	free(arena->display->memory);
	free(arena->display);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	endwin();
}
