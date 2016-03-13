/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:39:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/13 22:49:22 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "libft.h"
#include "parameters.h"
#include "instructions.h"
#include "operation.h"

extern t_op	g_op_tab[17];

void		decode_ocp(t_process *process, t_parameters *param)
{
	int select;
	int	decal;
	int temp;
	int i;

	select = 0xC0;
	i = 0;
	decal = 6;
	while (i < 3)
	{
		temp = process->pc[1] & select;
		param->type[i] = temp >> decal;
		select = select >> 2;
		decal -= 2;
		i++;
	}
}

void		params_value(t_process *process, t_parameters *param)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (param->type[i] == REG_CODE)
		{
			param->value[i] = ft_read_big_endian(process->pc + param->jump, 1);
			param->jump += 1;
		}
		else if (param->type[i] == DIR_CODE)
		{
			param->value[i] = ft_read_big_endian(process->pc + param->jump, DIR_SIZE);
			param->jump += DIR_SIZE;
		}
		else if (param->type[i] == IND_CODE)
		{
			param->value[i] = ft_read_big_endian(process->pc + param->jump, IND_SIZE);
			param->jump += IND_SIZE;
		}
		i++;
	}
}

int			check_registers(t_parameters param, t_process *process)
{
	if (process->registers == NULL)
		return (1);
	if ((param.type[0] == REG_CODE && process->registers[param.value[0]] == NULL)
	|| (param.type[1] == REG_CODE && process->registers[param.value[1]] == NULL)
	|| (param.type[2] == REG_CODE && process->registers[param.value[2]] == NULL))
		return (1);
	return (0);
}

int			execute_instruction(t_process *process)
{
	int(*instruction[16])(t_process *process) =
	{alive, load, store, addition, soustraction, ft_and, ft_or, ft_xor, zjump, load_index,
		store_index, ft_fork, long_load, long_load_index, long_fork, aff};
	int	i;

	i = 0;
	while (g_op_tab[i].op_code != process->pc[0] && i < 16)
		i++;
	if (i == 16)
		return (1);
	return ((*instruction[i])(process));
}

int			store_index(t_process *process)
{
	t_parameters	param;

	decode_ocp(process, &param);
	param.jump = 2;
	if (param.type[1] != 1)
		param.type[1] = 3;
	if (param.type[2] != 1)
		param.type[2] = 3;
	params_value(process, &param);
	if (param.value[0] > REG_NUMBER || check_registers(param, process) == 1)
		return (param.jump);
	ft_memcpy(process->pc + param.value[1] + param.value[2],
			process->registers[param.value[0] - 1], REG_SIZE);
	return (param.jump);
}
