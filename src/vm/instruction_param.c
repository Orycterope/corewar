/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction_param.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 15:39:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/08 19:05:40 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "libft.h"
#include "parameters.h"
#include "instructions.h"
#include "operation.h"
#include "read_write.h"

extern t_op	g_op_tab[];

void		decode_ocp(t_process *process, t_parameters *param, int i)
{
	int		select;
	int		decal;
	int		temp;
	int		j;

	select = 0xC0;
	j = 0;
	decal = 6;
	while (j < g_op_tab[i].param_nbr && j < 4)
	{
		temp = mem(PC + 1, 1, PA, process)[0] & select;
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
			param->value[i] = rm(mem(PC + param->jump, 1, PA, process), 1, PP);
			param->jump += 1;
		}
		else if (param->type[i] == DIR_CODE && param->o != 11 && param->o != 10
				&& param->o != 14)
		{
			param->value[i] = rm(mem(PC + PJ, 1, PA, process), DIR_SIZE, PP);
			param->jump += DIR_SIZE;
		}
		else if (param->type[i] == 0)
			;
		else
		{
			param->value[i] = rm(mem(PC + PJ, 1, PA, process), IND_SIZE, PP);
			param->jump += IND_SIZE;
		}
		i++;
	}
}

int			check_registers(t_parameters *param, t_process *process, int j)
{
	int	i;

	i = 0;
	while (i < g_op_tab[j].param_nbr && i < 4)
	{
		if (param->type[i] == REG_CODE)
		{
			if (PR[param->value[i] - 1] == NULL || param->value[i] > REG_NUMBER
					|| param->value[i] < 1)
				return (1);
		}
		i++;
	}
	return (0);
}

int			execute_instruction(t_process *process)
{
	static int		(*instruction[16])(t_process *process, int i) =
	{alive, load, store, addition, soustraction, ft_and, ft_or, ft_xor, zjump,
		load_index, store_index, ft_fork, long_load, long_load_index, long_fork,
		aff};
	int				i;

	i = 0;
	while (g_op_tab[i].op_code != process->op_code && g_op_tab[i].name != NULL)
		i++;
	if (g_op_tab[i].name == NULL)
		return (1);
	return ((*instruction[i])(process, i));
}

int			check_param_error(t_parameters param, int i)
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
