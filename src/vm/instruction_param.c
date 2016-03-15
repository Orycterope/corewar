/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:39:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/15 23:27:14 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "libft.h"
#include "parameters.h"
#include "instructions.h"
#include "operation.h"

extern t_op	g_op_tab[];

void		decode_ocp(t_process *process, t_parameters *param, int i)
{
	int select;
	int	decal;
	int temp;
	int j;

	select = 0xC0;
	j = 0;
	decal = 6;
	while (j < g_op_tab[i].param_nbr && j < 4)
	{
		temp = process->pc[1] & select;
		param->type[j] = temp >> decal;
		select = select >> 2;
		decal -= 2;
		j++;
	}
}

void		params_value(t_process *process, t_parameters *param, int j)
{
	int	i;

	i = 0;
	while (i < g_op_tab[j].param_nbr && i < 4)
	{
		if (param->type[i] == REG_CODE)
		{
			param->value[i] = ft_read_big_endian(process->pc + param->jump, 1);
			param->jump += 1;
		}
		else if (param->type[i] == DIR_CODE && param->o != 11)
		{
			param->value[i] = RBE(process->pc + param->jump, DIR_SIZE);
			param->jump += DIR_SIZE;
		}
		else if (param->type[i] == 0)
			;
		else
		{
			param->value[i] = RBE(process->pc + param->jump, IND_SIZE);
			param->jump += IND_SIZE;
		}
		i++;
	}
}

int			check_registers(t_parameters *param, t_process *process, int j)
{
	int	i;

	i = 0;
	if (process->registers == NULL)
		return (1);
	while (i < g_op_tab[j].param_nbr && i < 4)
	{
		if (param->type[i] == REG_CODE)
		{
			if (PR[param->value[i]] == NULL || param->value[i] > REG_NUMBER)
				return (1);
		}
		i++;
	}
	return (0);
}

int			execute_instruction(t_process *process)
{
	int (*instruction[16])(t_process *process, int i) =
	{alive, load, store, addition, soustraction, ft_and, ft_or, ft_xor, zjump,
		load_index, store_index, ft_fork, long_load, long_load_index, long_fork,
		aff};
	int	i;
 
	i = 0;
	while (g_op_tab[i].op_code != process->pc[0] && g_op_tab[i].name != NULL)
		i++;
	if (i >= 16) // // 
		return (1);
	return ((*instruction[i])(process, i));
}

int			check_param_error(t_process *process, t_parameters param, int i)
{
	int	j;

	j = 0;
	while (j < g_op_tab[i].param_nbr && param.type[j])
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
	while (++j < g_op_tab[i].param_nbr && j < 4)
	{
		if ((g_op_tab[i].param_type[j] & param.type[j]) == 0)
			return (1);
	}
	return (0);
}


int			store_index(t_process *process, int i)
{
	t_parameters	param;

	param.o = 11;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || g_op_tab[i].param_nbr < 3
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		PV[0] = RBE(PR[PV[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA), REG_SIZE) % IDX_MOD;
	if (param.type[1] == REG_CODE)
		PV[1] = RBE(PR[PV[1] - 1], REG_SIZE) % IDX_MOD;
	else if (param.type[1] == IND_CODE)
		PV[1] = RBE(mem(process->pc + PV[1], 1, PA), REG_SIZE) % IDX_MOD;
	if (param.type[2] == REG_CODE)
		PV[2] = RBE(PR[PV[2] - 1], REG_SIZE) % IDX_MOD;
	else if (param.type[2] == IND_CODE)
		PV[2] = RBE(mem(process->pc + PV[2], 1, PA), REG_SIZE) % IDX_MOD;
	WBE(PV[0], mem(process->pc + PV[1] + PV[2], 1, PA), REG_SIZE);
	return (param.jump);
}
