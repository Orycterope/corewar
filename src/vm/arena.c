/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:05:42 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/11 19:08:22 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

t_arena	*create_arena(void)
{
	char	*memory;
	t_arena	*new;

	new = (t_arena *)ft_memalloc(sizeof(t_arena));
	memory = (char *)ft_memalloc(MEM_SIZE);
	new->memory = memory;
	new->players = NULL;
	new->cycle = 0;
	new->cycle_to_die = CYCLE_TO_DIE;
	new->last_check_cycle = 0;
	new->checks_without_decrement = 0;
	new->processes = NULL;
	new->dump_cycle = -1;
	return (new);
}

void	display_champions(t_arena *arena)
{
	t_player	*i;
	int			total;
	int			n;
	int			p;

	ft_putendl("Introducing contestants...");
	total = 0;
	i = arena->players;
	while (i != NULL)
	{
		total++;
		i = i->next;
	}
	n = total;
	while (n--)
	{
		i = arena->players;
		p = n;
		while (p--)
			i = i->next;
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !",
				i->id, i->champ_size, i->name, i->comment);
	}
}

void	dump_memory(t_arena *arena)
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0 && i != MEM_SIZE - 1)
			ft_printf("\n%0#6x : ", i);
		ft_printf("%02x", arena->memory[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	destroy_arena(t_arena *arena)
{
	while (arena->processes != NULL)
		kill_process(arena->processes);
	free(arena->memory);
	free(arena);
}
