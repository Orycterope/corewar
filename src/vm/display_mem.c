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

	arena->display->w_mem = newwin(MEM_SIZE / 64, 64 * 3 + 10, 5, 5);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != MEM_SIZE - 1)
			wprintw(arena->display->w_mem, "\n%0#6x : ", i);
		wprintw(arena->display->w_mem, "%02x ", (unsigned char)arena->memory[i]);
	}
	wrefresh(arena->display->w_mem);
}

int			highlight_pcs(t_arena *arena)
{
	int			p_nbr;
	t_process	*p;

	p_nbr = 0;
	p = arena->processes;
	attron(A_BOLD);
	while (p != NULL)
	{
		//attron(COLOR_PAIR(p->player * 10));
		mvprintw((int)(p->pc - arena->memory) / 64,
				((int)(p->pc - arena->memory) % 64) * 3 + 9,
				"%02x", (unsigned char)*(p->pc));
		//attroff(COLOR_PAIR(p->player * 10));
		p_nbr++;
		p = p->next;
	}
	attroff(A_BOLD);
	move(MEM_SIZE / 64, 0);
	return (p_nbr);
}

void		highlight_rw(t_arena *arena)
{
	t_d_update	*u;
	t_d_update	*next;

	move(0, 0);
	u = arena->display->updates;
	while (u != NULL)
	{
		next = u->next;
		wmove(arena->display->w_mem, u->index / 64, (u->index % 64) * 3 + 9);
		//attron(COLOR_PAIR(u->owner * 10 + u->reader));
		wprintw(arena->display->w_mem,
				"%02x",(unsigned char)arena->memory[u->index]);
		if (u->w_turns)
			u->w_turns--;
		if (u->r_turns)
			u->r_turns--;
		if (u->r_turns == 0 && u->w_turns == 0)
			remove_update_struct(u, arena);
		u = next;
	}
}
