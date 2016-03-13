/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_reg_d_ind.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 12:44:03 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/13 18:31:46 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_reg(char *str)
{
	int		i;
	int		reg_check;

	i = 1;
	reg_check = 0;
	if (ft_isdigit(str[i]) == 1)
		reg_check = ft_atoi(str + i);
	while (str[i] && str[i] != ',')
	{
		if (ft_isdigit(str[i]) != 1)
			error("reg error");
		i++;
	}
	if (str[0] != 'r' || reg_check < 0 || is_in_str('r', str) > 1)
		error("reg error");
}

void	check_direct(char *str)
{
	if (str[0] != '%' && is_in_str('%', str) != 1)
		error("direct error");
}

void	check_indirect(char *str)
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
