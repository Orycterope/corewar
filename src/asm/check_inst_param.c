/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 10:53:52 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/29 14:13:53 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_params(char *str, t_instruc *inst, t_data *data, int *order)
{
	int		i;

	i = 0;
	inst->trim = ft_strtrim(str);
	while (g_op[i].name != 0)
	{
		if (inst->opcode == g_op[i].op_code)
		{
			if (g_op[i].param_nbr == 1)
				if_one_param(i, data, inst, order);
			else if (g_op[i].param_nbr == 2)
				if_two_params(i, data, inst, order);
			else if (g_op[i].param_nbr == 3)
				if_three_params(i, data, inst, order);
		}
		i++;
	}
}

char	*check_comm(char *str, t_data *data)
{
	char	**comm;

	comm = NULL;
	if (is_in_str(COMMENT_CHAR, str) > 0)
	{
		if ((comm = ft_strsplit(str, COMMENT_CHAR)) == NULL)
			error_line(data, "Malloc error");
		return (comm[0]);
	}
	return (str);
}
