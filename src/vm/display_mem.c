#include "display.h"
#include "libft.h"
#include "arena.h"

t_d_update	*get_update_struct_of(int i, t_arena *arena)
{
	t_d_update	*u;
	t_d_update	*previous;

	u = arena->display->updates;
	previous = NULL;
	while (u != NULL && u->index != i)
	{
		previous = u;
		u = u->next;
	}
	if (u != NULL)
		return (u);
	u = (t_d_update *)malloc(sizeof(t_d_update));
	if (u == NULL)
		return (NULL);
	ft_bzero(u, sizeof(t_d_update));
	if (previous == NULL)
		arena->display->updates = u;
	else
		previous->next = u;
	u->index = i;
	return (u);
}

void		remove_update_struct(t_d_update *u, t_arena *arena)
{
	t_d_update	*previous;
	t_d_update	*current;

	if (arena->display->updates == u)
		arena->display->updates = arena->display->updates->next;
	else
	{
		previous = arena->display->updates;
		current = previous->next;
		while (current != u)
		{
			previous = current;
			current = current->next;
		}
		previous->next = current->next;
	}
	free(u);
}

void		init_mem_display(t_arena *arena)
{
	int	i;

	arena->display->w_bkp = newwin(MEM_SIZE / 64, 64 * 3 + 10, 5, 5); //remove 5
	arena->display->w_mem = newwin(MEM_SIZE / 64, 64 * 3 + 10, 5, 5); //remove 5 // coord useless ?
	arena->display->w_pcs = newwin(MEM_SIZE / 64, 64 * 3 + 10, 5, 5); //remove 5 // coord useless ?
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != MEM_SIZE - 1)
		{
			if (i != 0)
				wprintw(arena->display->w_bkp, "\n");
			wprintw(arena->display->w_bkp, "%0#6x : ", i);
		}
		wprintw(arena->display->w_bkp, "%02x ", (unsigned char)arena->memory[i]);
	}
}

int			highlight_pcs(t_arena *arena)
{
	int			p_nbr;
	t_process	*p;

	p_nbr = 0;
	p = arena->processes;
	werase(arena->display->w_pcs);
	while (p != NULL)
	{
		wattron(arena->display->w_pcs, COLOR_PAIR(p->player) | A_BOLD);
		mvwprintw(arena->display->w_pcs,
			   	(int)(p->pc - arena->memory) / 64,
				((int)(p->pc - arena->memory) % 64) * 3 + 9,
				"%02x", (unsigned char)*(p->pc));
		wattroff(arena->display->w_pcs, COLOR_PAIR(p->player) | A_BOLD);
		p_nbr++;
		p = p->next;
	}
	//move(MEM_SIZE / 64, 0); //
	return (p_nbr);
}

void		construct_color_pair(t_d_update *u)
{
	int		fg;
	int		bg;
	int		pair;

	pair = (u->owner * 10 + u->w_turns) * 100 + (u->reader * 10 + u->r_turns);
	fg = COLOR_WHITE;
	bg = COLOR_BLACK;
	if (u->owner != 0)
		fg = 100 + u->owner * 10 + ((float)u->w_turns / D_WRITE_TURNS * 7);
	if (u->reader != 0)
		bg = 100 + u->reader * 10 + ((float)u->r_turns / D_READ_TURNS * 7);
	//init_pair(u->index + 10, fg, bg);
	init_pair(pair, fg, bg);
}

void		highlight_rw(t_arena *arena)
{
	t_d_update	*u;
	t_d_update	*next;
	int		pair; //

	//wmove(arena->display->w_mem, 0, 0); //
	u = arena->display->updates;
	while (u != NULL)
	{
		pair = u->owner;
		//pair = u->owner * 1000 + u->w_turns * 100 + u->reader * 10 + u->r_turns + 10;
		next = u->next;
		wmove(arena->display->w_bkp, u->index / 64, (u->index % 64) * 3 + 9);
		wattron(arena->display->w_bkp, COLOR_PAIR(pair));
		wprintw(arena->display->w_bkp,
				"%02x",(unsigned char)arena->memory[u->index]);
		wattroff(arena->display->w_bkp, COLOR_PAIR(pair));
		if (u->w_turns)
			u->w_turns--;
		if (u->r_turns)
			u->r_turns--;
		if (u->r_turns == 0 && u->w_turns == 0)
			remove_update_struct(u, arena);
		u = next;
	}
}
