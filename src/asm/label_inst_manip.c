/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:52:23 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/16 16:03:11 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_add_lbl(char *buf, t_label *lbl_lst, t_data *data)
{
	t_label		*new_elem;
	char		**sp_lbl_name;
	char		*colon_chr;

	new_elem = NULL;
	sp_lbl_name = NULL;
	if (is_in_str(LABEL_CHAR, buf) == 1)
	{
		if ((sp_lbl_name = ft_strsplit(buf, LABEL_CHAR)) == NULL)
			error_line(data, "Malloc error");
		if (!(colon_chr = ft_strchr(buf, LABEL_CHAR)) || buf == colon_chr)
			return (0);
		colon_chr = colon_chr - 1;
		if (is_in_str(*colon_chr, " \t") == 0 && (*colon_chr) != DIRECT_CHAR)
		{
			new_elem = lbl_new_elem(sp_lbl_name[0]);
			addend_lbl_lst(&lbl_lst, new_elem);
			return (1);
		}
	}
	return (0);
}

int			check_add_instruc(char *buf, t_label *lbl_lst, t_instruc **inst_lst,
								t_data *data)
{
	t_label		*tmp_lbl;
	char		*trim;
	char		**inst_line;
	t_instruc	*new_elem;

	init_check_add_instruc_var(&inst_line, &tmp_lbl, &trim, &new_elem);
	if (lbl_lst)
	{
		tmp_lbl = lbl_lst;
		while (tmp_lbl->next)
			tmp_lbl = tmp_lbl->next;
	}
	trim = real_trim(buf);
	if (is_in_str(' ', trim) > 0)
	{
		if ((inst_line = ft_strsplit(trim, ' ')) == NULL)
			error("Malloc error");
		if (is_in_str(SEPARATOR_CHAR, trim) == 0 && check_opcode_name(
			inst_line[0]) == 1)
			new_elem = inst_one_param(inst_line, inst_lst, data);
		else if (is_in_str(SEPARATOR_CHAR, trim) == 1 && check_opcode_name(
				inst_line[0]) == 1)
			new_elem = inst_two_params(inst_line, inst_lst, trim, data);
		else if (is_in_str(SEPARATOR_CHAR, trim) == 2 && check_opcode_name(
				inst_line[0]) == 1)
			new_elem = inst_three_params(inst_line, inst_lst, trim, data);
		else
			return (0);
		if (tmp_lbl && new_elem != NULL)
			tmp_lbl->insts = new_elem; // need to check
		return (1);
	}
	return (0);
}

t_instruc	*inst_one_param(char **inst_line, t_instruc **inst_lst,
						t_data *data)
{
	t_instruc	*new_elem;
	int			order;

	new_elem = NULL;
	order = 0;
	new_elem = inst_new_elem(inst_line[0]);
	check_opcode(inst_line[0], new_elem);
	check_params(inst_line[1], new_elem, data, &order);
	new_elem->param_1 = inst_line[1];
	addend_inst_lst(inst_lst, new_elem);
	return (new_elem);
}

t_instruc	*inst_two_params(char **inst_line, t_instruc **inst_lst, char *trim,
								t_data *data)
{
	t_instruc	*new_elem;
	char		**inst_params;
	int			order;

	new_elem = NULL;
	inst_params = NULL;
	order = 0;
	new_elem = inst_new_elem(inst_line[0]);
	check_opcode(inst_line[0], new_elem);
	check_params(inst_line[1], new_elem, data, &order);
	new_elem->param_1 = inst_line[1];
	if ((inst_params = ft_strsplit(trim, SEPARATOR_CHAR)) == NULL)
		error("Malloc error");
	check_params(inst_params[1], new_elem, data, &order);
	new_elem->param_2 = ft_pass_space_tab(inst_line[1]);
	addend_inst_lst(inst_lst, new_elem);
	return (new_elem);
}

t_instruc	*inst_three_params(char **inst_line, t_instruc **inst_lst,
			char *trim, t_data *data)
{
	t_instruc	*new_elem;
	char		**inst_params;
	int			order;

	new_elem = NULL;
	inst_params = NULL;
	order = 0;
	new_elem = inst_new_elem(inst_line[0]);
	check_opcode(inst_line[0], new_elem);
	check_params(inst_line[1], new_elem, data, &order);
	new_elem->param_1 = inst_line[1];
	if ((inst_params = ft_strsplit(trim, SEPARATOR_CHAR)) == NULL)
		error("Malloc error");
	check_params(inst_params[1], new_elem, data, &order);
	new_elem->param_2 = ft_pass_space_tab(inst_line[1]);
	check_params(inst_params[2], new_elem, data, &order);
	new_elem->param_3 = ft_pass_space_tab(inst_line[2]);
	addend_inst_lst(inst_lst, new_elem);
	return (new_elem);
}
