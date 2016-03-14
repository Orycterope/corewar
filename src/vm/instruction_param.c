/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:39:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/14 23:53:26 by adubedat         ###   ########.fr       */
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
		else if (param->type[i] == DIR_CODE && param->o != 11)
		{
			param->value[i] = ft_read_big_endian(process->pc + param->jump, DIR_SIZE);
			param->jump += DIR_SIZE;
		}
		else if (param->type[i] == 0)
			;
		else
		{
			param->value[i] = ft_read_big_endian(process->pc + param->jump, IND_SIZE);
			param->jump += IND_SIZE;
		}
		i++;
	}
}

int			check_registers(t_parameters *param, t_process *process)
{
	int	i;

	i = 0;
	if (process->registers == NULL)
		return (1);
	while (i < 3)
	{
		if (param->type[i] == REG_CODE)
		{
			if (process->registers[param->value[i]] == NULL || param->value[i] > REG_NUMBER)
				return (1);
		}
		i++;
	}
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

int			check_param_error(t_process *process, t_parameters param)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_op_tab[i].op_code != process->pc[0])
		i++;
	while (j < 3)
	{
		if (param.type[j] == REG_CODE)
			param.type[j++] = T_REG;
		else if (param.type[j] == DIR_CODE)
			param.type[j++] = T_DIR;
		else if (param.type[j] == IND_CODE)
			param.type[j++] = T_IND;
		else
			param.type[j++] = 0;
	}
	j = -1;
	while (++j < g_op_tab[i].param_nbr)
	{
		if ((g_op_tab[i].param_type[j] & param.type[j]) == 0)
			return (1);
	}
	return (0);
}


int			store_index(t_process *process)
{
	t_parameters	param;

	param.o = 11;
	decode_ocp(process, &param);
	param.jump = 2;
	params_value(process, &param);
	if (check_registers(&param, process) == 1 || check_param_error(process, param) == 1)
		return (param.jump);
	if (param.type[1] == REG_CODE)
		param.value[1] = ft_read_big_endian(process->registers[param.value[1] - 1], REG_SIZE) % IDX_MOD;
	else if (param.type[1] == IND_CODE)
		param.value[1] = ft_read_big_endian(process->pc + param.value[1], REG_SIZE) % IDX_MOD;
	if (param.type[2] == REG_CODE)
		param.value[2] = ft_read_big_endian(process->registers[param.value[2] - 1], REG_SIZE) % IDX_MOD;
	else if (param.type[2] == IND_CODE)
		return (param.jump);
	ft_memcpy(process->pc + param.value[1] + param.value[2],
			process->registers[param.value[0] - 1], REG_SIZE);
	return (param.jump);
}
