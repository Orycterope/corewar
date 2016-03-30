/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 17:32:37 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/30 20:03:58 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include "arena.h"

void	init_display(t_arena *arena)
{
	t_player	*p;
	int			color;

	initscr();
	cbreak();
	noecho();
	start_color();
	init_pair(0, COLOR_WHITE, COLOR_BLACK);
	p = arena->players;
	color = 0;
	while (p != NULL)
	{
		init_pair(p->id * 10 + 0, color % 6 + 1, 0);
		init_pair(p->id * 10 + 1, color % 6 + 1, 5);
		init_pair(p->id * 10 + 2, color % 6 + 1, 6);
		color++;
		p = p->next;
	}
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

void	print_mem(t_arena *arena)
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
	printw("Dumping memory at cycle %d (%d processus):", arena->cycle, highlight_pcs(arena));
	refresh();
	//getch();
}
