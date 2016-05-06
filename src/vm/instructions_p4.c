/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_p4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 14:15:33 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/06 22:37:04 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "parameters.h"
#include "arena.h"
#include "operation.h"
#include "read_write.h"

extern	t_op	g_op_tab[];

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
	|| check_param_error(param, i) == 1 || g_op_tab[i].param_nbr > 4)
		return (param.jump);
	//printf("P%5d | sti r%d ", process->number, (int)PV[0]);
	if (param.type[0] == REG_CODE)
		PV[0] = ft_read_big_endian(PR[PV[0] - 1], REG_SIZE);
	else if (param.type[0] == IND_CODE)
		PV[0] = rm(mem(process->pc + PV[0], 1, PA, process), REG_SIZE, PP);
	if (param.type[1] == REG_CODE)
		PV[1] = ft_read_big_endian(PR[PV[1] - 1], REG_SIZE);
	else if (param.type[1] == IND_CODE)
		PV[1] = rm(mem(process->pc + PV[1], 1, PA, process), REG_SIZE, PP);
	if (param.type[2] == REG_CODE)
		PV[2] = rm(PR[PV[2] - 1], REG_SIZE, PP);
	else if (param.type[2] == IND_CODE)
		PV[2] = rm(mem(process->pc + PV[2], 1, PA, process), REG_SIZE, PP);
	wm(PV[0], mem(process->pc + PV[1] + PV[2], 1, PA, process), REG_SIZE, PP);
	//printf("%d %d\n       | -> store to %d + %d = %d (with pc and mod %ld)\n", (int)PV[1], (int)PV[2], (int)PV[1], (int)PV[2], (int)PV[1] + (int)PV[2],
	//		process->pc + PV[2] + PV[1] - process->arena->memory);
	return (param.jump);
}

void	change_carry(t_process *process, unsigned int value)
{
	if (value == 0)
		process->carry = 1;
	else
		process->carry = 0;
}
