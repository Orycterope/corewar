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
	t_player	*p;
	int			color;

	initscr();
	cbreak();
	noecho();
	start_color();
	init_color(COLOR_WHITE, 400, 400, 400);
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	p = arena->players;
	color = 0;
	while (p != NULL)
	{
		init_pair(p->id * 10 + 0, color % 6 + 1, 0);
		init_pair(p->id * 10 + 1, color % 6 + 1, 0);
		init_pair(p->id * 10 + 2, color % 6 + 1, 0);
		color++;
		p = p->next;
	}
	arena->display = (t_display *)ft_memalloc(sizeof(t_display));
	arena->display->memory = (char *)ft_memalloc(MEM_SIZE);
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

static void	highlight_rw(t_arena *arena)
{
	int		i;
	int		player;
	int		turns;
	char	c;

	i = 0;
	move(0, 0);
	while (i < MEM_SIZE)
	{
		turns = arena->display->memory[i] & 0x07;
		if (turns != 0)
		{
			c = arena->display->memory[i];
			player = c >> 5;
			if ((c & 0x18) == 0x18)
				attron(COLOR_PAIR(player * 10 + 3));
			else if (c & 0x10)
				attron(COLOR_PAIR(player * 10 + 1));
			else if (c & 0x08)
				attron(COLOR_PAIR(player * 10 + 2));
			mvprintw(i / 64, (i % 64) * 3 + 9,
				"%02x", (unsigned char)arena->memory[i]);
			attroff(COLOR_PAIR(player * 10 + 1));
			attroff(COLOR_PAIR(player * 10 + 2));
			attroff(COLOR_PAIR(player * 10 + 3));
			if (--turns == 0)
				arena->display->memory[i] = 0;
			else
				arena->display->memory[i] = (c & 0xF8) | turns;
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
	//getch();
}

void	destroy_display(t_arena *arena)
{
	free(arena->display->memory);
	free(arena->display);
	init_color(COLOR_WHITE, 1000, 1000, 1000);
	endwin();
}

