/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_inst_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 10:53:52 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/17 12:42:42 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_params(char *str, t_instruc *inst, t_data *data, int *order)
{
	int		i;
	char	*trim;

	i = 0;
	trim = ft_strtrim(str);
//	if (g_op[i].param_nbr < 0 && g_op[i].param_nbr > 5)
//		error_line(data, "Incorrect number of params");
	while (g_op[i].name != 0)
	{
		if (inst->opcode == g_op[i].op_code)
		{
			if (g_op[i].param_nbr == 1)
			{
				ft_putstr("1 param");
				if (g_op[i].param_type[0] == T_DIR)
				{
					if (is_direct(trim, data, inst, order) == 1)
						return ;
					else
						error_line(data, "incorrect param WTF u doing");
				}
				else if (g_op[i].param_type[0] == T_REG)
				{
					if (is_register(trim, data, inst, order) == 1)
						return ;
					else
						error_line(data, "incorrect param WTF u doing");
				}
				else
					error_line(data, "what happen OMG");
			}
			else if (g_op[i].param_nbr == 2)
			{
				ft_putstr("2 params");
				if (*order == 0)
				{
					if (g_op[i].param_type[*order] == (T_DIR | T_IND))
					{
						ft_putstr(" T_DIR | T_IND");
						if (is_direct(trim, data, inst, order) == 1)
							return ;
						else if (is_indirect(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");
					}
					else if (g_op[i].param_type[*order] == T_REG)
					{
						if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");
					}
					else
						error_line(data, "what happen OMG");
				}
				else if (*order == 1)
				{
					if (g_op[i].param_type[*order] == T_REG)
					{
						if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");
					}
					else if (g_op[i].param_type[*order] == (T_IND | T_REG))
					{
						if (is_indirect(trim, data, inst, order) == 1)
							return ;
						else if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");
					}
					else
						error_line(data, "what happen OMG");
				}
			}
			else if (g_op[i].param_nbr == 3)
			{
				ft_putstr("3 params");
				if (*order == 0)
				{
					if (g_op[i].param_type[*order] == T_REG)
					{
						if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");	
					}
					else if (g_op[i].param_type[*order] == (T_REG | T_DIR | T_IND))
					{
						if (is_register(trim, data, inst, order) == 1)
							return ;
						else if (is_direct(trim, data, inst, order) == 1)
							return ;
						else if (is_indirect(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");		
					}
					else
						error_line(data, "what happen OMG");
				}
				else if (*order == 1)
				{
					if (g_op[i].param_type[*order] ==  T_REG)
					{
						if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");	
					}
					else if (g_op[i].param_type[*order] == (T_REG | T_DIR | T_IND))
					{
						if (is_register(trim, data, inst, order) == 1)
							return ;
						else if (is_direct(trim, data, inst, order) == 1)
							return ;
						else if (is_indirect(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");
					}
					else if (g_op[i].param_type[*order] == (T_DIR | T_REG))
					{
						if (is_direct(trim, data, inst, order) == 1)
							return ;
						else if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");
					}
					else
						error_line(data, "what happen OMG");
				}
				else if (*order == 2)
				{
					if (g_op[i].param_type[*order] ==  T_REG)
					{
						if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");	
					}
					else if (g_op[i].param_type[*order] == (T_DIR | T_REG))
					{
						if (is_direct(trim, data, inst, order) == 1)
							return ;
						else if (is_register(trim, data, inst, order) == 1)
							return ;
						else
							error_line(data, "incorrect param WTF u doing");
					}
				}
			}
		}
		i++;
	}
//	ft_printf("->%X %D \n", inst->ocp, inst->ocp);
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
