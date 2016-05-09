/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_inst_manip_next.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:59:25 by rporcon           #+#    #+#             */
/*   Updated: 2016/05/09 14:02:56 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		check_all_params(char *trim, char **inst_line, t_data *data,
		int *ret)
{
	if (is_in_str(SEPARATOR_CHAR, trim) == 0 && check_opcode_name(
				inst_line[0]) == 1)
		inst_one_param(inst_line, data);
	else if (is_in_str(SEPARATOR_CHAR, trim) == 1 && check_opcode_name(
				inst_line[0]) == 1)
		inst_two_params(inst_line, trim, data);
	else if (is_in_str(SEPARATOR_CHAR, trim) == 2 && check_opcode_name(
				inst_line[0]) == 1)
		inst_three_params(inst_line, trim, data);
	else if (is_in_str(SEPARATOR_CHAR, trim) > 3 && ft_strchr(trim,
				COMMENT_CHAR) == NULL)
		error_line(data, "Incorrect number of params");
	else
		*ret = 0;
}

void		inst_one_param(char **inst_line, t_data *data)
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
	new_elem = inst_new_elem(ft_strdup(inst_line[0]));
	check_opcode(inst_line[0], new_elem);
	check_params(inst_line[1], new_elem, data, &order);
	new_elem->param_1 = no_comma(inst_line[1]);
	tmp_lbl = last_label(data);
	addend_inst_lst(&tmp_lbl->insts, new_elem);
}

void		inst_two_params(char **inst_line, char *trim,
								t_data *data)
{
	t_instruc	*new_elem;
	t_label		*tmp_lbl;
	char		**inst_params;
	int			order;

	new_elem = NULL;
	inst_params = NULL;
	order = 0;
	new_elem = inst_new_elem(ft_strdup(inst_line[0]));
	check_opcode(inst_line[0], new_elem);
	check_params(inst_line[1], new_elem, data, &order);
	new_elem->param_1 = no_comma(inst_line[1]);
	if ((inst_params = ft_strsplit(trim, SEPARATOR_CHAR)) == NULL)
		error("Malloc error");
	if (inst_params[1] == NULL)
		error_line(data, "Incorrect input parameters");
	check_params(inst_params[1], new_elem, data, &order);
	new_elem->param_2 = ft_strdup(ft_pass_space_tab(inst_params[1]));
	tmp_lbl = last_label(data);
	addend_inst_lst(&tmp_lbl->insts, new_elem);
	free_strsplit(inst_params);
}

void		inst_three_params(char **inst_line, char *trim, t_data *data)
{
	t_instruc	*new_elem;
	t_label		*tmp_lbl;
	char		**inst_params;
	int			order;

	new_elem = NULL;
	inst_params = NULL;
	order = 0;
	new_elem = inst_new_elem(ft_strdup(inst_line[0]));
	check_opcode(inst_line[0], new_elem);
	check_params(inst_line[1], new_elem, data, &order);
	new_elem->param_1 = no_comma(inst_line[1]);
	if ((inst_params = ft_strsplit(trim, SEPARATOR_CHAR)) == NULL)
		error("Malloc error");
	if (inst_params[1] == NULL || inst_params[2] == NULL)
		error_line(data, "Incorrect input parameters");
	check_params(inst_params[1], new_elem, data, &order);
	new_elem->param_2 = ft_strdup(ft_pass_space_tab(inst_params[1]));
	check_params(inst_params[2], new_elem, data, &order);
	new_elem->param_3 = ft_strdup(ft_pass_space_tab(inst_params[2]));
	tmp_lbl = last_label(data);
	addend_inst_lst(&tmp_lbl->insts, new_elem);
	free_strsplit(inst_params);
}
