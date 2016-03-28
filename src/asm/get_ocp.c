/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ocp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:18:55 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 17:19:00 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		get_ocp(int ocp, int index)
{
	if (index >= 0 && index <= 3)
	{
		if (index == 0)
			ocp = (ocp >> 6) & 3;
		if (index == 1)
			ocp = (ocp >> 4) & 3;
		if (index == 2)
			ocp = (ocp >> 2) & 3;
		if (index == 3)
			ocp = ocp & 3;
		return (ocp);
	}
	return (-1);
}

int		get_params_size_ocp_2(int ret, int i, int *arr, t_instruc *inst)
{
	if (ft_strcmp(inst->name, "live") != 0 &&
			ft_strcmp(inst->name, "zjump") != 0 &&
			ft_strcmp(inst->name, "fork") != 0 &&
			ft_strcmp(inst->name, "lfork") != 0)
		ret++;
	while (i < 4)
	{
		if (arr[i] == REG_CODE)
		{
			ret += 1;
		}
		if (arr[i] == DIR_CODE)
		{
			if (ft_strcmp(inst->name, "sti") == 0 ||
					ft_strcmp(inst->name, "lldi") == 0 ||
					ft_strcmp(inst->name, "ldi") == 0)
				ret += 2;
			else
				ret += 4;
		}
		if (arr[i] == IND_CODE)
			ret += 2;
		i++;
	}
	return (ret);
}

int		get_params_size_ocp(t_instruc *inst)
{
	int		arr[4];

	arr[0] = get_ocp(inst->ocp, 0);
	arr[1] = get_ocp(inst->ocp, 1);
	arr[2] = get_ocp(inst->ocp, 2);
	arr[3] = get_ocp(inst->ocp, 3);
	if (inst->ocp == -4)
		return (4);
	if (inst->ocp == -2)
		return (2);
	return (get_params_size_ocp_2(0, 0, arr, inst));
}
