/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   if_params.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/17 16:12:47 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/17 16:22:35 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


void	if_one_param(int i, t_data *data, t_instruc *inst, int *order)
{
	if (g_op[i].param_type[0] == T_DIR)
	{
		if (is_direct(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "incorrect param WTF u doing");
	}
	else if (g_op[i].param_type[0] == T_REG)
	{
		if (is_register(inst->trim, data, inst, order) == 1)
			return ;
		else
			error_line(data, "incorrect param WTF u doing");
	}
	else
		error_line(data, "what happen OMG");
}

void	if_two_params(int i, t_data *data, t_instruc *inst, int *order)
{
	if (*order == 0)
	{
		if (g_op[i].param_type[*order] == (T_DIR | T_IND))
		{
			if (is_direct(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_indirect(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");
		}
		else if (g_op[i].param_type[*order] == T_REG)
		{
			if (is_register(inst->trim, data, inst, order) == 1)
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
			if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");
		}
		else if (g_op[i].param_type[*order] == (T_IND | T_REG))
		{
			if (is_indirect(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");
		}
		else
			error_line(data, "what happen OMG");
	}
}

void	if_three_params(int i, t_data *data, t_instruc *inst, int *order)
{
	if (*order == 0)
	{
		if (g_op[i].param_type[*order] == T_REG)
		{
			if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");	
		}
		else if (g_op[i].param_type[*order] == (T_REG | T_DIR | T_IND))
		{
			if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_direct(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_indirect(inst->trim, data, inst, order) == 1)
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
			if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");	
		}
		else if (g_op[i].param_type[*order] == (T_REG | T_DIR | T_IND))
		{
			if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_direct(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_indirect(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");
		}
		else if (g_op[i].param_type[*order] == (T_DIR | T_REG))
		{
			if (is_direct(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_register(inst->trim, data, inst, order) == 1)
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
			if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");	
		}
		else if (g_op[i].param_type[*order] == (T_DIR | T_REG))
		{
			if (is_direct(inst->trim, data, inst, order) == 1)
				return ;
			else if (is_register(inst->trim, data, inst, order) == 1)
				return ;
			else
				error_line(data, "incorrect param WTF u doing");
		}
	}
}
