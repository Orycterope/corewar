/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:34:56 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/07 18:24:01 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "parameters.h"
#include "arena.h"
#include "operation.h"
#include "read_write.h"
#include "instructions.h"

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
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr < 3
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = rm(mem(process->pc + PV[0], 1, PA, process), REG_SIZE, PA);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = rm(mem(process->pc + PV[1], 1, PA, process), REG_SIZE, PA);
	printf("P%5d | and %d %d r%d\n", process->number, (int)PV[0], (int)PV[1], (int)PV[2]);
	ft_write_big_endian((PV[0] & PV[1]), PR[PV[2] - 1], REG_SIZE);
	change_carry(process, (PV[0] & PV[1]));
	return (param.jump);
}

int		ft_or(t_process *process, int i)
{
	t_parameters	param;

	param.o = 7;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || param.type[2] != REG_CODE
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr < 3
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = rm(mem(process->pc + PV[0], 1, PA, process), REG_SIZE, PA);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = rm(mem(process->pc + PV[1], 1, PA, process), REG_SIZE, PA);
	ft_write_big_endian((PV[0] | PV[1]), PR[PV[2] - 1], REG_SIZE);
	change_carry(process, (PV[0] | PV[1]));
	return (param.jump);
}
int		ft_xor(t_process *process, int i)
{
	t_parameters	param;

	param.o = 8;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || param.type[2] != REG_CODE
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr < 3
	|| g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = rm(mem(process->pc + PV[0], 1, PA, process), REG_SIZE, PA);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = rm(mem(process->pc + PV[1], 1, PA, process), REG_SIZE, PA);
	printf("P%5d | xor %d %d r%d\n", process->number, (int)PV[0], (int)PV[1], (int)PV[2]);
	ft_write_big_endian((PV[0] ^ PV[1]), PR[PV[2] - 1], REG_SIZE);
	change_carry(process, (PV[0] ^ PV[1]));
	return (param.jump);
}
int		zjump(t_process *process, int i)
{
	t_parameters	param;

	i += 1;
	param.o = 9;
	param.type[0] = IND_CODE;
	param.value[0] = rm(mem(process->pc + 1, 1, PA, process), IND_SIZE, PA);
	printf("P%5d | zjmp %hd", process->number, (short)PV[0]);
	if (process->carry == 1)
	{
		printf(" OK\n");
		return ((short)PV[0] % IDX_MOD);
	}
	else
		printf(" FAILED\n");
	return (1 + IND_SIZE);
}

int		load_index(t_process *process, int i)
{
	t_parameters	param;

	param.o = 10;
	decode_ocp(process, &param, i);
	param.jump = 1 + g_op_tab[i].has_ocp;
	if (g_op_tab[i].has_ocp == 0)
		return (1);
	params_value(process, &param, i);
	if (check_registers(&param, process, i) == 1 || g_op_tab[i].param_nbr < 3
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr > 4)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = RBE(process->registers[param.value[0] - 1], REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = RBE(process->registers[param.value[1] - 1], REG_SIZE);
	printf("P%5d | ldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %ld)\n", process->number, (int)PV[0], (int)PV[1], (int)PV[2], (int)PV[0], (int)PV[1], (int)PV[0] + (int)PV[1], mem(process->pc + (int)PV[0] + (int)PV[1], 1, PA, process) - process->arena->memory);
	PV[0] = rm(mem(process->pc + PV[0] + PV[1], 1, PA, process), REG_SIZE, PA);
	if (param.type[2] == REG_CODE)
		WBE(PV[0], PR[PV[2] -1], REG_SIZE);
	else if (param.type[2] == IND_CODE)
		wm(PV[0], mem(process->pc + PV[0], 1, PA, process), REG_SIZE, PA);
	return (param.jump);
}