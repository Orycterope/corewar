/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_d_ind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 12:44:03 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/20 20:39:20 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_reg(char *str, t_data *data)
{
	int		i;
	int		reg_check;

	i = 1;
	reg_check = 0;
	if (ft_isdigit(str[i]) == 1)
		reg_check = ft_atoi(str + i);
	while (str[i] != '\0' && str[i] != SEPARATOR_CHAR)
	{
		if (ft_isdigit(str[i]) != 1)
			error_line(data, "reg error");
		i++;
	}
	if (str[0] != 'r' || reg_check < 0 || is_in_str('r', str) > 1)
		error_line(data, "reg error");
}

void	check_direct(char *str, t_data *data)
{
	int		i;

	i = 1;
	if (str[0] != DIRECT_CHAR && is_in_str(DIRECT_CHAR, str) != 1)
		error_line(data, "direct error");
	if (ft_isdigit(str[i]) == 1)
	{
		while (str[i] != '\0' && str[i] != SEPARATOR_CHAR)
		{
			if (ft_isdigit(str[i]) != 1)
				error_line(data, "direct error");
			i++;
		}
	}
}

void	check_indirect(char *str, t_data *data)
{
	int		i;
	int		ind_check;

	i = 1;
	ind_check = 0;
	if (str[0] == LABEL_CHAR)
	{
		if (ft_isdigit(str[i]) == 1)
			ind_check = ft_atoi(str + i);
		while (str[i] && str[i] != SEPARATOR_CHAR)
		{
			if (ft_isdigit(str[i]) != 1)
				error_line(data, "indirect error");
			i++;
		}
	}
	if (str[0] != LABEL_CHAR && ft_isdigit(str[0]) != 1)
		error_line(data, "indirect error");
}
