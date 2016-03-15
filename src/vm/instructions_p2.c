/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:34:56 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/15 23:27:09 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "parameters.h"
#include "arena.h"
#include "operation.h"

extern	t_op	g_op_tab[];

int		ft_and(t_process *process, int i)
{
	t_parameters	param;

	param.o = 6;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || param.type[2] != REG_CODE
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr < 3
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA), REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = RBE(mem(process->pc + PV[1], 1, PA), REG_SIZE);
	ft_write_big_endian((PV[0] & PV[1]), PR[PV[2] - 1], REG_SIZE);
	process->carry = 1;
	return(param.jump);
}

int		ft_or(t_process *process, int i)
{
	t_parameters	param;

	param.o = 6;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || param.type[2] != REG_CODE
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr < 3
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA), REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = RBE(mem(process->pc + PV[1], 1, PA), REG_SIZE);
	ft_write_big_endian((PV[0] | PV[1]), PR[PV[2] - 1], REG_SIZE);
	process->carry = 1;
	return(param.jump);
}
int		ft_xor(t_process *process, int i)
{
	t_parameters	param;

	param.o = 6;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || param.type[2] != REG_CODE
	|| check_param_error(process, param, i) == 1 || g_op_tab[i].param_nbr < 3
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = RBE(mem(process->pc + PV[0], 1, PA), REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = RBE(mem(process->pc + PV[1], 1, PA), REG_SIZE);
	ft_write_big_endian((PV[0] ^ PV[1]), PR[PV[2] - 1], REG_SIZE);
	process->carry = 1;
	return(param.jump);
}
int		zjump(t_process *process, int i)
{
	return(1);
}

int		load_index(t_process *process, int i)
{
	return(1);
}
