/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 10:53:52 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/13 18:31:03 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	check_first_1param(char *str, t_instruc *inst)
{
	char	ocp;
	
	ocp = '0';
	if (inst->opcode == 12 || inst->opcode == 15 || inst->opcode == 9
		|| inst->opcode == 1)
	{
		if (str[0] == DIRECT_CHAR)
			check_direct(str);
		return (ocp);
	}
	else if (inst->opcode == 16 && str[0] == 'r')
	{
		check_reg(str);
		return (ocp);
	}
	return (ocp);
}

char	check_first_2param(char *str, t_instruc *inst)
{
	char	ocp;

	ocp = '0';
	if (inst->opcode == 3 && str[0] == 'r')
	{
		check_reg(str);
		return (ocp);
	}
	else if (inst->opcode == 2 || inst->opcode == 13)
	{
		if (str[0] == DIRECT_CHAR)
			check_direct(str);
		else
			check_indirect(str);
		return (ocp);
	}
	return (0);
}

char	check_second_2param(char *str, t_instruc *inst)
{
	char	ocp;
	char	*trim;

	ocp = '0';
	trim = ft_strtrim(str);
	if ((inst->opcode == 2 || inst->opcode == 13) && trim[0] == 'r')
	{
		check_reg(trim);
		return (ocp);
	}
	else if (inst->opcode == 3)
	{
		check_indirect(trim);
		if (trim[0] == 'r')
			check_reg(trim);
		return (ocp);
	}
	return (0);
}

char	check_first_3param(char *str, t_instruc *inst)
{
	char	ocp;

	ocp = '0';
	if ((inst->opcode == 11 || inst->opcode == 4 || inst->opcode == 5) &&
		str[0] == 'r')
	{
		check_reg(str);
		return (ocp);
	}
	else if (inst->opcode == 6 || inst->opcode == 7 || inst->opcode == 8 ||
			inst->opcode == 10 || inst->opcode == 14)
	{
		if (str[0] == 'r')
			check_reg(str);
		else if (str[0] == DIRECT_CHAR)
			check_direct(str);
		else 
			check_indirect(str);
	}
	return (ocp);
}

char	check_second_3param(char *str, t_instruc *inst)
{
	char	ocp;
	char	*trim;

	ocp = '0';
	trim = ft_strtrim(str);
	if ((inst->opcode == 4 || inst->opcode == 5) && str[0] == 'r')
	{
		check_reg(trim);
		return (ocp);
	}
	else if (inst->opcode == 11 || inst->opcode == 6 || inst->opcode == 7 ||
			inst->opcode == 8)
	{
		if (trim[0] == 'r')
			check_reg(trim);
		else if (trim[0] == DIRECT_CHAR)
			check_direct(trim);
		else
			check_indirect(trim);
		return (ocp);
	}
	else if (inst->opcode == 10 || inst->opcode == 14)
	{
		if (trim[0] == DIRECT_CHAR)
			check_direct(trim);	
		else if (trim[0] == 'r')
			check_reg(trim);
		return (ocp);
	}
	return (ocp);
}

char	check_third_3param(char *str, t_instruc *inst)
{
	char	ocp;
	char	*trim;

	ocp = '0';
	trim = ft_strtrim(str);
	if ((inst->opcode == 4 || inst->opcode == 5 || inst->opcode == 6 ||
		inst->opcode == 7 || inst->opcode == 8 || inst->opcode == 10 ||
		inst->opcode == 14) && str[0] == 'r')
	{
		check_reg(trim);
		return (ocp);
	}
	else if (inst->opcode == 1)
	{
		if (trim[0] == DIRECT_CHAR)
			check_direct(trim);
		else if (trim[0] == 'r')
			check_reg(trim);
	}
	return (ocp);
}
