/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_reg_d_ind.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 10:40:33 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/29 11:23:29 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_direct(char *trim, t_data *data, t_instruc *inst, int *order)
{
	if (trim[0] == DIRECT_CHAR)
	{
		check_direct(trim, data);
		inst->ocp = set_ocp(inst->ocp, *order, 2);
		*order = *order + 1;
		return (1);
	}
	return (0);
}

int		is_indirect(char *trim, t_data *data, t_instruc *inst, int *order)
{
	if (trim[0] == ':' || ft_isdigit(trim[0]) || trim[0] == '-'
		|| trim[0] == '+')
	{
		check_indirect(trim, data);
		inst->ocp = set_ocp(inst->ocp, *order, 3);
		*order = *order + 1;
		return (1);
	}
	return (0);
}

int		is_register(char *trim, t_data *data, t_instruc *inst, int *order)
{
	if (trim[0] == 'r')
	{
		check_reg(trim, data);
		inst->ocp = set_ocp(inst->ocp, *order, 1);
		*order = *order + 1;
		return (1);
	}
	return (0);
}

int		without_ocp(char *trim, t_data *data, t_instruc *inst)
{
	if (trim[0] == DIRECT_CHAR)
	{
		check_direct(trim, data);
		inst->ocp = -2;
		return (1);
	}
	return (0);
}

int		without_ocp_live(char *trim, t_data *data, t_instruc *inst)
{
	if (trim[0] == DIRECT_CHAR)
	{
		check_direct(trim, data);
		inst->ocp = -4;
		return (1);
	}
	return (0);
}
