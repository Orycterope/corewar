/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:55:35 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/20 16:34:55 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "execution.h"
#include "libft.h"

static char **create_copy_registers(char **registers, int player_id)
{
	int			i;
	char		**new;

	new = (char **)malloc(sizeof(char *) * REG_NUMBER);
	if (new == NULL)
		return (NULL);
	i = -1;
	while (++i < REG_NUMBER)
	{
		new[i] = (char *)malloc(REG_SIZE);
		if (new[i] == NULL)
			new[i] = NULL;
		else if (registers == NULL)
		{
			if (i == 0)
				ft_write_big_endian(player_id, new[0], REG_SIZE);
			else
				ft_bzero(new[i], REG_SIZE);
		}
		else
			ft_memcpy(new[i], registers[i], REG_SIZE);
	}
	return (new);
}

/** Allocates a new process structure
 ** when registers param is NULL it initiates empty registers,
 ** otherwise they are copied from existent registers
 **/

void	create_process(int player, char *pc, t_arena *arena, char **registers)
{
	t_process	*new;

	new = (t_process*)ft_memalloc(sizeof(t_process));
	new->player = player;
	new->registers = create_copy_registers(registers, player);
	new->pc = pc;
	new->carry = 0;
	new->cycles_to_wait = get_wait_time(new) - 1;
	new->lives = 0;
	new->arena = arena;
	new->next = arena->processes;
	arena->processes = new;
}

void	fork_process(t_process *process, char *pc)
{
	create_process(process->player, pc, process->arena, process->registers);
	process->arena->processes->carry = process->carry;
	process->arena->processes->lives = process->lives;
}

void	kill_process(t_process *process)
{
	t_process	*i;
	int			r;

	if (process->arena->processes == process)
		process->arena->processes = process->next;
	else
	{
		i = process->arena->processes;
		while (i->next != process)
			i = i->next;
		i->next = process->next;
	}
	if (process->registers != NULL)
	{
		r = -1;
		while (++r < REG_NUMBER && process->registers[r] != NULL)
			free(process->registers[r]);
		free(process->registers);
	}
	free(process);
}
