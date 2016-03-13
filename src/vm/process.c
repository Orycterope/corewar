/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:55:35 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/13 16:32:29 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"

static char **create_copy_registers(char **registers, int player_id)
{
	int			i;
	char		**new;

	i = -1;
	new = (char **)ft_memalloc(REG_NUMBER);
	if (new == NULL)
		return (NULL);
	while (++i < REG_NUMBER)
	{
		new[i] = (char *)malloc(REG_SIZE);
		if (new[i] == NULL)
			return (new);
		if (registers == NULL)
			ft_bzero(new[i], REG_SIZE);
		else
			ft_memcpy(new[i], registers[i], REG_SIZE);
	}
	player_id++;
	//ft_write_big_endian((long long)player_id, reg[0], REG_SIZE);
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
	new->cycles_to_wait = 0;
	new->lives = 0;
	new->arena = arena;
	new->next = arena->processes;
	arena->processes = new;
}

void	fork_process(t_process *process, char *pc)
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
	if (process->registers != NULL)
	{
		r = -1;
		while (++r < REG_NUMBER && process->registers[r] != NULL)
			free(process->registers[r]); //wy u not work ?
		free(process->registers);
	}
	free(process);
}
