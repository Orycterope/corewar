/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 10:53:52 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/12 19:07:15 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


char	check_first_2param(char *str, t_instruc *inst)
{
	char	ocp;

	ocp = '0'; // just for init error, wait ocp_fct
	if (inst->opcode == 3)
	{
		check_reg(str);
		return (ocp);
	}
	else if (inst->opcode == 2 || inst->opcode == 13)
	{
		check_direct(str);
		check_indirect(str);
		return (ocp);
	}
	return (0);
}

char	check_second_2param(char *str, t_instruc *inst)
{
	char	ocp;

	ocp = '0'; // just for init error, wait ocp_fct
	if (inst->opcode == 2 || inst->opcode == 13)
	{
		check_reg(str);
		return (ocp);
	}
	else if (inst->opcode == 3)
	{
		check_indirect(str);
		check_reg(str);
		return (ocp);
	}
	return (0);
}

void	check_reg(char *str)
{
	int		i;
	int		reg_check;

	i = 1;
	reg_check = 0;
	if (ft_isdigit(str[i]))
		reg_check = ft_atoi(str + i);
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			error("reg error");
		i++;
	}
	if (str[0] != 'r' || reg_check < 0 || reg_check > 99 || is_in_str('r',
				str) > 1)
		error("reg error");
}

void	check_direct(char *str)
{
	if (str[0] != '%' && is_in_str('%', str) != 1)
		error("direct error");
}

void	check_indirect(char *str)
{
	if (str[0] != ':' && ft_isdigit(str[0]) == 0)
		error("indirect error");
}
