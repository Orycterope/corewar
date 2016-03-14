/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_p1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:17:18 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/14 23:53:24 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "parameters.h"

int		alive(t_process *process)
{
	unsigned int	param;
	t_player		*temp;

	param = ft_read_big_endian(process->pc + 1, 4);
	process->lives += 1;
	temp = process->arena->players;
	while (temp != NULL && temp->id != param)
	{
		temp = temp->next;
	}
	if (temp != NULL)
		temp->last_live = process->arena->cycle;
	return(5);
}

int		load(t_process *process)
{
	t_parameters	param;

	param.o = 2;
	decode_ocp(process, &param);
	param.jump = 2;
	params_value(process, &param);
	if (check_registers(&param, process) == 1 || check_param_error(process, param) == 1)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = ft_read_big_endian(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		param.value[0] = ft_read_big_endian(process->pc + param.value[0], REG_SIZE) % IDX_MOD;
	ft_write_big_endian(param.value[0], process->registers[param.value[1] - 1], REG_SIZE);
	return(param.jump);
}

int		store(t_process *process)
{
	return(1);
}

int		addition(t_process *process)
{
	return(1);
}

int		soustraction(t_process *process)
{
	return(1);
}
