/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 15:44:24 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 15:45:44 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	arena->display->w_bkp = newwin(MEM_SIZE / 64, 64 * 3 + 10, 0, 0);
	arena->display->w_mem = newwin(MEM_SIZE / 64, 64 * 3 + 10, 0, 0);
	arena->display->w_pcs = newwin(MEM_SIZE / 64, 64 * 3 + 10, 0, 0);
	i = -1;
	while (++i < MEM_SIZE)
	{
		if (i % 64 == 0 && i != MEM_SIZE - 1)
		{
			if (i != 0)
				wprintw(arena->display->w_bkp, "\n");
			wprintw(arena->display->w_bkp, "%0#6x : ", i);
		}
		wprintw(arena->display->w_bkp, "%02x ",
				(unsigned char)arena->memory[i]);
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
	return (p_nbr);
}

void		highlight_rw(t_arena *arena)
{
	t_d_update	*u;
	t_d_update	*next;
	int			pair;

	u = arena->display->updates;
	while (u != NULL)
	{
		next = u->next;
		pair = u->owner * 10 + u->w_turns + MAX_PLAYERS + 1;
		wmove(arena->display->w_bkp, u->index / 64, (u->index % 64) * 3 + 9);
		wattron(arena->display->w_bkp, COLOR_PAIR(pair));
		wprintw(arena->display->w_bkp,
				"%02x", (unsigned char)arena->memory[u->index]);
		wattroff(arena->display->w_bkp, COLOR_PAIR(pair));
		u->w_turns--;
		if (u->w_turns == 0)
			remove_update_struct(u, arena);
		u = next;
	}
}
