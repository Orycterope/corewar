/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 10:53:52 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/16 16:03:07 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_params(char *str, t_instruc *inst, t_data *data, int *order)
{
	int		i;
	char	*trim;

	i = 0;
	trim = ft_strtrim(str);
	if (g_op[i].param_nbr < 0 && g_op[i].param_nbr > 5)
		error_line(data, "Incorrect number of params");
	while (g_op[i].name != 0)
	{
		if (inst->opcode == g_op[i].op_code)
		{
			if (trim[0] == DIRECT_CHAR)
			{
				check_direct(trim, data);
				inst->ocp = set_ocp(inst->ocp, *order, 2);
				*order = *order + 1;
				return ;
			}
			else if (trim[0] == 'r')
			{
				check_reg(trim, data);
				inst->ocp = set_ocp(inst->ocp, *order, 1);
				*order = *order + 1;
				return ;
			}
			else
			{
				check_indirect(trim, data);
				inst->ocp = set_ocp(inst->ocp, *order, 3);
				*order = *order + 1;
				return ;
			}
		}
		i++;
	}
//	ft_printf("->%X %D \n", inst->ocp, inst->ocp);
}
