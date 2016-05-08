/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:55:35 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 21:24:04 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "execution.h"
#include "libft.h"

void	create_copy_registers(t_process *p, t_process *parent, int player)
{
	int		i;

	i = -1;
	while (++i < REG_NUMBER)
	{
		if (parent == NULL)
		{
			if (i == 0)
				ft_write_big_endian(player, p->registers[0], REG_SIZE);
			else
				ft_bzero(p->registers[i], REG_SIZE);
		}
		else
			ft_memcpy(p->registers[i], parent->registers[i], REG_SIZE);
	}
}

/*
** Allocates a new process structure
** when registers param is NULL it initiates empty registers,
** otherwise they are copied from existent registers
*/

void	create_process(int player, char *pc, t_arena *arena, t_process *parent)
{
	t_process	*new;
	static int	i = 0;

	i++;
	new = (t_process*)malloc(sizeof(t_process));
	if (new == NULL)
		return ;
	new->player = player;
	new->pc = pc;
	new->carry = (parent == NULL) ? 0 : parent->carry;
	new->lives = (parent == NULL) ? 0 : parent->lives;
	new->count_lives = 0;
	new->cycles_to_wait = -1;
	new->op_code = 0;
	new->arena = arena;
	new->next = arena->processes;
	new->number = i;
	create_copy_registers(new, parent, player);
	arena->processes = new;
}

void	fork_process(t_process *process, char *pc)
{
	create_process(process->player, pc, process->arena, process);
}

void	kill_process(t_process *process)
{
	t_process	*i;

	if (process->arena->processes == process)
		process->arena->processes = process->next;
	else
	{
		i = process->arena->processes;
		while (i->next != process)
			i = i->next;
		i->next = process->next;
	}
	free(process);
}

int		count_processes(t_arena *arena)
{
	t_process	*p;
	int			i;

	i = 0;
	p = arena->processes;
	while (p != NULL)
	{
		i++;
		p = p->next;
	}
	return (i);
}
