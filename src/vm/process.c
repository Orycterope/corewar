/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:55:35 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/08 21:17:37 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static char **create_copy_registers(char **registers, int pid)
{
	int			i;
	char		**new;

	i = -1;
	new = (char **)ft_malloc(REG_NUMBER);
	while (++i < REG_NUMBER)
	{
		new[i] = (char *)ft_malloc(REG_SIZE);
		if (registers == NULL)
			bzero(new[i], REG_SIZE);
		else
			ft_memcpy(new[i], registers[i], REG_SIZE);
	}
	//TODO: write pid to r1 in big endian
	return (new);
}

/** Allocates a new process structure
 ** when registers param is NULL it initiates empty registers,
 ** otherwise they are copied from existent registers
 **/

void	create_process(int player, int pc, t_arena *arena, char **registers)
{
	t_process	*new;

	new = (t_process*)ft_malloc(sizeof(t_process));
	new->pid = arena->next_available_pid++;
	new->player = player;
	new->registers = create_copy_registers(registers, new->pid);
	new->pc = pc;
	new->carry = 0;
	new->cycles_to_wait = 0;
	new->lives = 0;
	new->arena = arena;
	new->next = arena->processes;
	arena->processes = new;
	return (new);
}

void	fork_process(t_process *process, int pc)
{
	create_process(process->player, pc, process->arena, process->registers);
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
	r = -1;
	while (++r < REG_NUMBER)
		free(registers[r]);
	free(registers);
	free(process);
}
