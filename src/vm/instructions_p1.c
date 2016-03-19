/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_p1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:17:18 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/16 16:23:28 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "parameters.h"
#include "operation.h"

extern	t_op	g_op_tab[];

int		alive(t_process *process, int i)
{
	t_parameters	param;
	t_player		*temp;

	param.type[0] = DIR_CODE;
	param.value[0] = RBE(mem(process->pc + 1, 1, PA, process), DIR_SIZE);
	process->lives += 1;
	temp = process->arena->players;
	while (temp != NULL && temp->id != param.value[0])
	{
		temp = temp->next;
	}
	if (temp != NULL)
		temp->last_live = process->arena->cycle;
	return(1 + DIR_SIZE);
}

int		load(t_process *process, int i)
{
	t_parameters	param;

	param.o = 2;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || param.type[1] != REG_CODE
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr < 2
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = ft_read_big_endian(PR[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA, process), REG_SIZE);
	ft_write_big_endian(param.value[0], PR[param.value[1] - 1], REG_SIZE);
	change_carry(process, PV[0]);
	return (param.jump);
}

int		store(t_process *process, int i)
{
	t_parameters	param;

	param.o = 3;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || g_op_tab[i].param_nbr < 2
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = ft_read_big_endian(PR[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA, process), REG_SIZE);
	if (param.type[1] == REG_CODE)
		ft_write_big_endian(PV[0], PR[PV[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		WBE(PV[0], mem(process->pc + PV[1], 1, PA, process), REG_SIZE);
	return (param.jump);
}

int		addition(t_process *process, int i)
{
	t_parameters	param;

	param.o = 4;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || g_op_tab[i].param_nbr < 3
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr > 4
	|| param.type[2] != REG_CODE)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = ft_read_big_endian(PR[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA, process), REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = ft_read_big_endian(PR[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = RBE(mem(process->pc + PV[1], 1, PA, process), REG_SIZE);
	WBE(PV[0] + PV[1], PR[PV[2] - 1], REG_SIZE);
	change_carry(process, (PV[0] + PV[1]));
	return (param.jump);
}

int		soustraction(t_process *process, int i)
{
	t_parameters	param;

	param.o = 5;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || g_op_tab[i].param_nbr < 3
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr > 4
	|| param.type[2] != REG_CODE)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = ft_read_big_endian(PR[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA, process), REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = ft_read_big_endian(PR[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = RBE(mem(process->pc + PV[1], 1, PA, process), REG_SIZE);
	WBE(PV[0] - PV[1], PR[PV[2] - 1], REG_SIZE);
	change_carry(process, (PV[0] - PV[1]));
	return (param.jump);
}
