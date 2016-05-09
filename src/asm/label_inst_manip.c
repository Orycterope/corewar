/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:52:23 by rporcon           #+#    #+#             */
/*   Updated: 2016/05/09 14:01:28 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int			check_add_lbl(char *buf, t_data *data)
{
	t_label		*new_elem;
	char		**sp_lbl_name;
	char		*colon_chr;

	init_check_add_lbl(&new_elem, &sp_lbl_name, &colon_chr);
	if (is_in_str(LABEL_CHAR, buf) >= 1)
	{
		if ((sp_lbl_name = ft_strsplit(buf, LABEL_CHAR)) == NULL)
			error_line(data, "Malloc error");
		if (check_add_lbl_cut(buf, &colon_chr, sp_lbl_name) == 1)
			return (0);
		if (is_in_str(*colon_chr, " \t") == 0 && (*colon_chr) != DIRECT_CHAR)
		{
			if (str_is_in_str(LABEL_CHARS, sp_lbl_name[0]) == 1)
				error_line(data, "Incorrect label name");
			new_elem = lbl_new_elem(ft_strdup(sp_lbl_name[0]));
			addend_lbl_lst(&data->label, new_elem);
			free_strsplit(sp_lbl_name);
			return (1);
		}
		free_strsplit(sp_lbl_name);
	}
	return (0);
}

int			check_add_lbl_cut(char *buf, char **colon_chr, char **sp_lbl_name)
{
	if (!(*colon_chr = ft_strchr(buf, LABEL_CHAR)) || buf == *colon_chr)
	{
		free_strsplit(sp_lbl_name);
		return (1);
	}
	*colon_chr = *colon_chr - 1;
	return (0);
}

t_label		*last_label(t_data *data)
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

void		check_first_lbl(t_data *data)
{
	t_label		*new_elem;

	new_elem = NULL;
	if (data->label == NULL)
	{
		new_elem = lbl_new_elem(ft_strdup("COMMENT_CHARfirst"));
		addend_lbl_lst(&data->label, new_elem);
	}
}

int			check_add_instruc(char *buf, t_data *data)
{
	char		*trim;
	char		**inst_line;
	int			ret;

	buf = check_comm(buf, data);
	check_first_lbl(data);
	init_check_add_instruc(&inst_line, &trim, &ret);
	trim = real_trim(buf);
	if (is_in_str(' ', trim) > 0)
	{
		ret = 1;
		if ((inst_line = ft_strsplit(trim, ' ')) == NULL)
			error("Malloc error");
		check_all_params(trim, inst_line, data, &ret);
		free_strsplit(inst_line);
	}
	return (ret);
}
