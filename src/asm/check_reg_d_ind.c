/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_d_ind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 12:44:03 by rporcon           #+#    #+#             */
/*   Updated: 2016/05/09 14:42:31 by rporcon          ###   ########.fr       */
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
	{
		reg_check = ft_atoi(str + i);
		if (reg_check > REG_NUMBER)
			error_line(data, "Incorrect number of register");
	}
	while (str[i] != '\0' && str[i] != SEPARATOR_CHAR)
	{
		if (ft_isdigit(str[i]) != 1)
			error_line(data, "Register error, incorrect input");
		i++;
	}
	if (str[0] != 'r' || reg_check < 0 || is_in_str('r', str) > 1 || i > 3)
		error_line(data, "Register error, incorrect input");
}

void	check_direct(char *str, t_data *data)
{
	int		i;

	i = 1;
	if (str[0] != DIRECT_CHAR && is_in_str(DIRECT_CHAR, str) != 1)
		error_line(data, "Incorrect direct input");
	if (ft_isdigit(str[i]) == 1)
	{
		while (str[i] != '\0' && str[i] != SEPARATOR_CHAR)
		{
			if (ft_isdigit(str[i]) != 1)
				error_line(data, "Direct error, incorrect input");
			i++;
		}
	}
}

void	check_indirect(char *str, t_data *data)
{
	int		i;
	int		ind_check;

	i = 0;
	ind_check = 0;
	if (str[i] == LABEL_CHAR)
	{
		i++;
		if (ft_isdigit(str[i]) == 1)
		{
			ind_check = ft_atoi(str + i);
			while (str[i] && str[i] != SEPARATOR_CHAR)
			{
				if (ft_isdigit(str[i]) != 1)
					error_line(data, "Indirect error, incorrect input");
				i++;
			}
		}
	}
	i = 0;
	if (str[i] == '-')
		i++;
	if (str[i] != LABEL_CHAR && ft_isdigit(str[i]) != 1)
		error_line(data, "Indirect error, incorrect input");
}
