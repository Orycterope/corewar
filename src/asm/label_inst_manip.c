/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:52:23 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/19 19:13:03 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_add_lbl(char *buf, t_label **lbl_lst, t_data *data)
{
	t_label		*new_elem;
	char		**sp_lbl_name;
	char		*colon_chr;

	new_elem = NULL;
	sp_lbl_name = NULL;
	colon_chr = NULL;
	if (is_in_str(LABEL_CHAR, buf) == 1)
	{
		if ((sp_lbl_name = ft_strsplit(buf, LABEL_CHAR)) == NULL)
			error_line(data, "Malloc error");
		if (!(colon_chr = ft_strchr(buf, LABEL_CHAR)) || buf == colon_chr)
			return (0);
		colon_chr = colon_chr - 1;
		if (is_in_str(*colon_chr, " \t") == 0 && (*colon_chr) != DIRECT_CHAR)
		{
			if (str_is_in_str(LABEL_CHARS, sp_lbl_name[0]) == 1)
				error_line(data, "Incorrect label name");
			new_elem = lbl_new_elem(sp_lbl_name[0]);
			addend_lbl_lst(lbl_lst, new_elem);
			return (1);
		}
	}
	return (0);
}

t_label		*add_last_label(t_data *data)
{
	t_label		*tmp_lbl;

	tmp_lbl = data->label;
	if (tmp_lbl)
	{
		while (tmp_lbl->next)
			tmp_lbl = tmp_lbl->next;
	}
	return (tmp_lbl);
}

int			check_add_instruc(char *buf, t_data *data)
{
	char		*trim;
	char		**inst_line;
	t_instruc	*new_elem;

	buf = check_comm(buf, data);
	init_check_add_instruc_var(&inst_line, &trim, &new_elem);
	trim = real_trim(buf);
	if (is_in_str(' ', trim) > 0)
	{
		if ((inst_line = ft_strsplit(trim, ' ')) == NULL)
			error("Malloc error");
		if (is_in_str(SEPARATOR_CHAR, trim) == 0 && check_opcode_name(
			inst_line[0]) == 1)
			new_elem = inst_one_param(inst_line, data);
		else if (is_in_str(SEPARATOR_CHAR, trim) == 1 && check_opcode_name(
				inst_line[0]) == 1)
			new_elem = inst_two_params(inst_line, trim, data);
		else if (is_in_str(SEPARATOR_CHAR, trim) == 2 && check_opcode_name(
				inst_line[0]) == 1)
			new_elem = inst_three_params(inst_line, trim, data);
		else if (is_in_str(SEPARATOR_CHAR, trim) > 3 && ft_strchr(trim,
				COMMENT_CHAR) == NULL)
			error_line(data, "Incorrect number of params");
		else
			return (0);
		return (1);
	}
	return (0);
}

t_instruc	*inst_one_param(char **inst_line, t_data *data)
{
	t_instruc	*new_elem;
	t_label		*tmp_lbl;
	int			order;
	int			i;

	new_elem = NULL;
	order = 0;
	i = 0;
	while (inst_line[i])
		i++;
	if (i > 2)
		error_line(data, "Incorrect number of params");
	new_elem = inst_new_elem(inst_line[0]);
	check_opcode(inst_line[0], new_elem);
	check_params(inst_line[1], new_elem, data, &order);
	new_elem->param_1 = inst_line[1];
	tmp_lbl = add_last_label(data);
	addend_inst_lst(&tmp_lbl->insts, new_elem);
	return (new_elem);
}

t_instruc	*inst_two_params(char **inst_line, char *trim,
								t_data *data)
{
	t_instruc	*new_elem;
	t_label		*tmp_lbl;
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
	new_elem->param_2 = ft_pass_space_tab(inst_params[1]);
	tmp_lbl = add_last_label(data);
	addend_inst_lst(&tmp_lbl->insts, new_elem);
	return (new_elem);
}

t_instruc	*inst_three_params(char **inst_line, char *trim, t_data *data)
{
	t_instruc	*new_elem;
	t_label		*tmp_lbl;
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
	new_elem->param_2 = ft_pass_space_tab(inst_params[1]);
	check_params(inst_params[2], new_elem, data, &order);
	new_elem->param_3 = ft_pass_space_tab(inst_params[2]);
	tmp_lbl = add_last_label(data);
	addend_inst_lst(&tmp_lbl->insts, new_elem);
	return (new_elem);
}
