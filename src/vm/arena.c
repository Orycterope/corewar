/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:05:42 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/15 17:30:32 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

char	*mem(char *pc, char	*dst, int idx, t_arena *arena)
{
	char	*ptr;

	ptr = pc;
	if (idx)
		ptr = pc + (dst - pc) % IDX_MOD;
	ptr = arena->memory + (ptr - arena->memory) % MEM_SIZE;
	return (ptr);
}

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

	ft_putendl("Introducing contestants...");
	total = 0;
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

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 32 == 0 && i != MEM_SIZE - 1)
			ft_printf("\n%0#6x : ", i);
		ft_printf("%02x", (unsigned char)arena->memory[i]);
		ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

void	destroy_arena(t_arena *arena)
{
	while (arena->processes != NULL)
		kill_process(arena->processes);
	free_players(arena);
	free(arena->memory);
	free(arena);
}
