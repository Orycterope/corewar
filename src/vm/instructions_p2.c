/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions_p2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:34:56 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/14 23:51:04 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "process.h"
#include "parameters.h"


int		ft_and(t_process *process)
{
	t_parameters	param;

	param.o = 6;
	decode_ocp(process, &param);
	param.jump = 2;
	params_value(process, &param);
	if (check_registers(&param, process) == 1 || check_param_error(process, param) == 1)
		return (param.jump);
	if (param.type[0] == REG_CODE)
		param.value[0] = ft_read_big_endian(process->registers[param.value[0] - 1], REG_SIZE);
	if (param.type[1] == REG_CODE)
		param.value[1] = ft_read_big_endian(process->registers[param.value[1] - 1], REG_SIZE);
	ft_write_big_endian((param.value[0] & param.value[1]), process->registers[param.value[2] - 1], REG_SIZE);
	process->carry = 1;
	return(param.jump);
}

int		ft_or(t_process *process)
{
	return(1);
}
int		ft_xor(t_process *process)
{
	return(1);
}
int		zjump(t_process *process)
{
	return(1);
}

int		load_index(t_process *process)
{
	return(1);
}
