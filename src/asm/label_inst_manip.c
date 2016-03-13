/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:52:23 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/13 18:31:42 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_add_lbl(char *buf, t_label *lbl_lst)
{
	t_label	*new_elem;
	char	**sp_lbl_name;
	char	*colon_chr;

	new_elem = NULL;
	sp_lbl_name = NULL;
	if (is_in_str(LABEL_CHAR, buf) == 1)
	{
		if ((sp_lbl_name = ft_strsplit(buf, LABEL_CHAR)) == NULL)
			error("Malloc error");
		colon_chr = ft_strchr(buf, LABEL_CHAR);
		colon_chr = colon_chr - 1;
		if (*colon_chr != DIRECT_CHAR && *colon_chr != ' '
			&& *colon_chr != '	')
		{
			new_elem = lbl_new_elem(sp_lbl_name[0]);
			addend_lbl_lst(&lbl_lst, new_elem);
		}
		return (1);
	}
	return (0);
}

int		check_add_instruc(char *buf, t_label *lbl_lst, t_instruc
		*inst_lst)
{
	t_instruc	*new_elem;
	t_label		*tmp_lbl;
	char		*trim;
	char		**inst_line;

	new_elem = NULL;
	tmp_lbl = NULL;
	inst_line = NULL;
	trim = NULL;
	if (lbl_lst)
	{
		tmp_lbl = lbl_lst;
		while (tmp_lbl->next)
			tmp_lbl = tmp_lbl->next;
	}
	if ((trim = ft_strtrim(buf)) == NULL)
		error("Malloc error");
	if (is_in_str(' ', trim) > 0)
	{
		if ((inst_line = ft_strsplit(trim, ' ')) == NULL)
			error("Malloc error");
		new_elem = inst_new_elem(inst_line[0]);
		if (is_in_str(SEPARATOR_CHAR, trim) == 0 && check_opcode_name(
			inst_line[0]) == 1)
		{
			if (check_opcode(inst_line[0], new_elem) == 1)
				check_opcode_suit(inst_line[0], new_elem);
			check_first_1param(inst_line[0], new_elem);
			new_elem->param_1 = inst_line[1];
			addend_inst_lst(&inst_lst, new_elem);
			if (tmp_lbl)
				tmp_lbl->insts = new_elem;	
			return (1);
		}
		else if (is_in_str(SEPARATOR_CHAR, trim) == 1 && check_opcode_name(
				inst_line[0]) == 1)
		{
			if (check_opcode(inst_line[0], new_elem) == 1)
				check_opcode_suit(inst_line[0], new_elem);
			// first p
			check_first_2param(inst_line[1], new_elem);
			new_elem->param_1 = inst_line[1];
			if ((inst_line = ft_strsplit(trim, SEPARATOR_CHAR)) == NULL)
				error("Malloc error");
			// second p
			check_second_2param(inst_line[1], new_elem);
			new_elem->param_2 = ft_pass_space_tab(inst_line[1]);
			addend_inst_lst(&inst_lst, new_elem);
			if (tmp_lbl)
				tmp_lbl->insts = new_elem;
			return (1);
		}
		else if (is_in_str(SEPARATOR_CHAR, trim) == 2 && check_opcode_name(
				inst_line[0]) == 1)
		{
			if (check_opcode(inst_line[0], new_elem) == 1)
				check_opcode_suit(inst_line[0], new_elem);
			check_first_3param(inst_line[1], new_elem);
			new_elem->param_1 = inst_line[1];
			if ((inst_line = ft_strsplit(trim, SEPARATOR_CHAR)) == NULL)
				error("Malloc error");
			check_second_3param(inst_line[1], new_elem);
			new_elem->param_2 = ft_pass_space_tab(inst_line[1]);
			check_third_3param(inst_line[2], new_elem);
			new_elem->param_3 = ft_pass_space_tab(inst_line[2]);
			addend_inst_lst(&inst_lst, new_elem);
			if (tmp_lbl)
				tmp_lbl->insts = new_elem;
			return (1);
		}
	}
	return (0);
}

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
