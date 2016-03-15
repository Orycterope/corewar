/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:28:11 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/15 17:57:02 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_opcode_name(char *str)
{
	int		i;

	i = 0;
	while (g_op[i].name != 0)
	{
		if (ft_strcmp(str, g_op[i].name) == 0)
			return (1);
		i++;
	}
	return (0);
}

int		check_opcode(char *str, t_instruc *inst)
{
	int		i;

	i = 0;
	while (g_op[i].name != 0)
	{
		if (ft_strcmp(str, g_op[i].name))
		{
			inst->opcode = g_op[i].op_code;
			return (1);
		}
		i++;
	}
	return (0);
}
