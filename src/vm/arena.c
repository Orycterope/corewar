/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:05:42 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 18:04:11 by tvermeil         ###   ########.fr       */
/*   Updated: 2016/05/06 22:24:57 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "process.h"
#include "display.h"

char	*mem(char *ptr, int idx, t_arena *arena, t_process *process)
{
	int	temp;

	temp = ptr - process->pc;
	temp %= MEM_SIZE;
	if (idx)
		temp %= IDX_MOD;
	if (process->pc + temp < arena->memory)
		return (process->pc + temp + MEM_SIZE);
	if (process->pc + temp >= arena->memory + MEM_SIZE)
		return (process->pc + temp - MEM_SIZE);
	return (process->pc + temp);
}

t_arena	*create_arena(void)
{
	char	*memory;
	t_arena	*new;

	new = (t_arena *)ft_memalloc(sizeof(t_arena));
	memory = (char *)ft_memalloc(MEM_SIZE);
	new->memory = memory;
	new->players = NULL;
	new->cycle = 1;
	new->cycle_to_die = CYCLE_TO_DIE;
	new->last_check_cycle = 0;
	new->checks_without_decrement = 0;
	new->processes = NULL;
	new->dump_cycle = -1;
	new->display = NULL;
	return (new);
}

void	display_champions(t_arena *arena)
{
	t_player	*i;

	ft_putendl("Introducing contestants...");
	i = arena->players;
	while (i != NULL)
	{
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i->id, i->champ_size, i->name, i->comment);
		i = i->next;
	}
}

void	dump_memory(t_arena *arena)
{
	int		i;
	int		p_nbr;
	t_process	*p;

	p = arena->processes;
	p_nbr = 0;
	while (p != NULL)
	{
		p = p->next;
		p_nbr++;
	}
	ft_printf("\nDumping memory at cycle %d (%d processus):", arena->cycle, p_nbr);
	i = 0;
	while (i < MEM_SIZE)
	{
		p = arena->processes;
		if (i % 64 == 0 && i != MEM_SIZE - 1) // should be % 32 !!!!!
			ft_printf("\n%0#6x : ", i);
		while (p != NULL)
		{
			if (p->pc == &(arena->memory[i]))
				ft_printf("\x1B[0;3%dm", p->player % 6 + 1);
			p = p->next;
		}
		ft_printf("%02x", (unsigned char)arena->memory[i]);
		ft_putstr("\x1B[0m");
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	destroy_arena(t_arena *arena)
{
	if (arena->display != NULL)
		destroy_display(arena);
	while (arena->processes != NULL)
		kill_process(arena->processes);
	free_players(arena);
	free(arena->memory);
	free(arena);
}
