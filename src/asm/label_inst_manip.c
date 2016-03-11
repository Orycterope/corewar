/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_manip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:52:23 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/11 21:59:03 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		check_add_lbl(char *buf)
{
	t_label	*lbl_lst;
	t_label	*new_elem;
	char	**sp_lbl_name;

	lbl_lst = NULL;
	new_elem = NULL;
	sp_lbl_name = NULL;
	if (check_num_of_: == 1)
	{
		if ((sp_lbl_name = ft_strsplit(buf, ":")) == NULL)
			error("malloc error");
		free_strsplit(sb_lbl_name);
		new_elem = lbl_new_elem(buf);
		new_elem->name = sp_lbl_name[1];
		addend_lbl_list(&lbl_lst, new_elem);
		return (1);
	}
	return (0);
}

int		check_add_instruc(char *buf)
{
	t_instruc	*inst_lst;
	t_instruc	*new_elem;
	char		**inst_line;

	inst_lst = NULL;
	new_elem = NULL;
	inst_line = NULL;
}
