/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_d_ind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 12:44:03 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/17 12:42:47 by rporcon          ###   ########.fr       */
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
	while (str[i] != '\0' && str[i] != ',')
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
	if (str[0] != '%' && is_in_str('%', str) != 1)
		error_line(data, "direct error");
}

void	check_indirect(char *str, t_data *data)
{
	int		i;
	int		ind_check;

	i = 1;
	ind_check = 0;
	if (str[0] == ':')
	{
		if (ft_isdigit(str[i]) == 1)
			ind_check = ft_atoi(str + i);
		while (str[i] && str[i] != ',')
		{
			if (ft_isdigit(str[i]) != 1)
				error("indirect error");
			i++;
		}
	}
	if (str[0] != ':' && ft_isdigit(str[0]) != 1)
		error("indirect error");
}
