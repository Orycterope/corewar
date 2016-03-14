/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_opcode.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:28:11 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/14 16:28:36 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_opcode_name(char *str)
{
	if (ft_strcmp(str, "lfork") == 0 || ft_strcmp(str, "sti") == 0 ||
		ft_strcmp(str, "fork") == 0 || ft_strcmp(str, "lld") == 0 ||
		ft_strcmp(str, "ld") == 0 || ft_strcmp(str, "ld") == 0 ||
		ft_strcmp(str, "add") == 0 || ft_strcmp(str, "zjmp") == 0 ||
		ft_strcmp(str, "sub") == 0 || ft_strcmp(str, "ldi") == 0 ||
		ft_strcmp(str, "st") == 0 || ft_strcmp(str, "add") == 0 ||
		ft_strcmp(str, "live") == 0 || ft_strcmp(str, "xor") == 0 ||
		ft_strcmp(str, "lldi") == 0 || ft_strcmp(str, "add") == 0)
		return (1);
	return (0);
}

int		check_opcode(char *str, t_instruc *inst)
{
	if (ft_strcmp(str, "lfork") == 0)
		inst->opcode = 15;
	else if (ft_strcmp(str, "sti") == 0)
		inst->opcode = 11;
	else if (ft_strcmp(str, "fork") == 0)
		inst->opcode = 12;
	else if (ft_strcmp(str, "lld") == 0)
		inst->opcode = 13;
	else if (ft_strcmp(str, "ld") == 0)
		inst->opcode = 2;
	else if (ft_strcmp(str, "add") == 0)
		inst->opcode = 4;
	else if (ft_strcmp(str, "zjmp") == 0)
		inst->opcode = 9;
	else if (ft_strcmp(str, "sub") == 0)
		inst->opcode = 5;
	else if (ft_strcmp(str, "ldi") == 0)
		inst->opcode = 10;
	else if (ft_strcmp(str, "or") == 0)
		inst->opcode = 7;
	else
		return (1);
	return (0);
}

void	check_opcode_suit(char *str, t_instruc *inst)
{
	if (ft_strcmp(str, "st") == 0)
		inst->opcode = 3;
	else if (ft_strcmp(str, "aff") == 0)
		inst->opcode = 16;
	else if (ft_strcmp(str, "live") == 0)
		inst->opcode = 1;
	else if (ft_strcmp(str, "xor") == 0)
		inst->opcode = 8;
	else if (ft_strcmp(str, "lldi") == 0)
		inst->opcode = 14;
	else if (ft_strcmp(str, "add") == 0)
		inst->opcode = 6;
}
