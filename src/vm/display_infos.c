#include "display.h"
#include "arena.h"

void		init_info_display(t_arena *arena)
{
	int			line;
	t_player	*player;

	arena->display->w_info = newwin(20, 50, 10, 64 * 3 + 15);
	wtimeout(arena->display->w_info, 0);
	wprintw(arena->display->w_info, "Dumping memory at cycle %-5d (%d processus)\
\n\n\nCycles per second : %4d", 0, count_processes(arena), 0);
	player = arena->players;
	line = 5;
	while (player != NULL)
	{
		mvwprintw(arena->display->w_info, line, 0,
				"Player %s :\n\tProcessus : %6d\n\tLast live: %6d", player->name, 1, 0);
		line += 4;
		player = player->next;
	}
}

void		update_infos(t_arena *a)
{
	t_player	*player;
	t_process	*p;
	int			line;
	int			i;

	p = a->processes;
	mvwprintw(a->display->w_info, 0, 24, "%-5d (%d processus)",
			a->cycle, count_processes(a));
	mvwprintw(a->display->w_info, 3, 20, "%4d", a->display->cps);
	line = 6;
	player = a->players;
	while (player != NULL)
	{
		i = 0;
		p = a->processes;
		while (p != NULL)
		{
			if (p->player == player->id)
				i++;
			p = p->next;
		}
		mvwprintw(a->display->w_info, line, 20, "%6d", i);
		mvwprintw(a->display->w_info, line + 1, 20, "%6d", player->last_live);
		line += 4;
		player = player->next;
	}
}

void		check_keystroke(t_arena *a)
{
	char	c;
	char	cont;
	int		*cps;

	cont = 1;
	while ((a->display->running == 0 && !a->display->quitting) || cont == 1)
	{
		cont = 0;
		cps = &(a->display->cps);
		c = wgetch(a->display->w_info);
		if (c == 's')
			break;
		else if (c == ' ')
			a->display->running = !a->display->running;
		else if (c == 'j')
			*cps += (*cps < 1000 ) ? 10 : 1000 - *cps;
		else if (c == 'k')
			*cps -= (*cps >= 10 ) ? 10 : *cps;
		else if (c == 'l')
			*cps += (*cps < 1000 ) ? 1 : 0;
		else if (c == ';')
			*cps -= (*cps > 0 ) ? 1 : 0;
		else if (c == 'q')
			a->display->quitting = 1;
		update_infos(a);
	}
}
