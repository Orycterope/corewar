/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_include_in_cip.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 11:59:12 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/20 20:33:10 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_direct(char *trim, t_data *data, t_instruc *inst, int *order)
{
	if (trim[0] == DIRECT_CHAR)
	{
		check_direct(trim, data);
		if (trim[0] == DIRECT_CHAR && trim[1] == LABEL_CHAR)
			inst->lbl_addr = trim + 2;
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

int		without_ocp(char *trim, t_data *data, t_instruc *inst, int *order)
{
	if (trim[0] == DIRECT_CHAR)
	{
		check_direct(trim, data);
		if (trim[0] == DIRECT_CHAR && trim[1] == LABEL_CHAR)
			inst->lbl_addr = trim + 2;
		inst->ocp = -1;
		*order = *order + 1;
		return (1);
	}
	return (0);
}
