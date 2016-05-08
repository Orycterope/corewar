/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_p3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:37:16 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/08 19:53:11 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "parameters.h"
#include "arena.h"
#include "operation.h"
#include "read_write.h"
#include "instructions.h"

extern	t_op g_op_tab[];

int		ft_fork(t_process *process, int i)
{
	t_parameters	param;

	i += 1;
	param.o = 12;
	param.type[0] = DIR_CODE;
	param.value[0] = rm(mem(process->pc + 1, 1, PA, process), IND_SIZE, PP);
	fork_process(process, mem(PC + (short)PV[0] % IDX_MOD, 1, PA, process));
	return (1 + IND_SIZE);
}

int		long_load(t_process *process, int i)
{
	t_parameters	param;

	param.o = 2;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || param.type[1] != REG_CODE
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr < 2
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = ft_read_big_endian(PR[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = rm(mem(process->pc + PV[0], 0, PA, process), REG_SIZE, PP);
	ft_write_big_endian(param.value[0], PR[param.value[1] - 1], REG_SIZE);
	change_carry(process, PV[0]);
	return (param.jump);
}

int		long_load_index(t_process *process, int i)
{
	t_parameters	param;

	param.o = 14;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || g_op_tab[i].param_nbr < 3
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	PV[0] = rm(mem(process->pc + PV[0] + PV[1], 0, PA, process), REG_SIZE, PP);
	if (param.type[2] == REG_CODE)
		WBE(PV[0], PR[PV[2] - 1], REG_SIZE);
	else if (param.type[2] == IND_CODE)
		wm(PV[0], mem(process->pc + PV[0], 0, PA, process), REG_SIZE, PP);
	return (param.jump);
}

int		long_fork(t_process *process, int i)
{
	t_parameters	param;

	i += 1;
	param.o = 15;
	param.type[0] = DIR_CODE;
	param.value[0] = rm(mem(process->pc + 1, 0, PA, process), IND_SIZE, PP);
	fork_process(process, mem(process->pc + (short)PV[0], 0, PA, process));
	return (1 + IND_SIZE);
}

int		aff(t_process *process, int i)
{
	t_parameters	param;

	param.o = 16;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || g_op_tab[i].param_nbr > 4
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr < 1)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = rm(mem(process->pc + PV[0], 1, PA, process), REG_SIZE, PP);
	ft_putchar(PV[0] % 256);
	return (param.jump);
}
