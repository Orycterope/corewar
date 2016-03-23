/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_special.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:10:39 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 17:10:47 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	set_address(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[1] == LABEL_CHAR)
	{
		val = label_exist(data, param + 2, lbl_name);
		val = val * addr_diff(data, param + 2, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param + 1);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
}

void	set_live(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[1] == LABEL_CHAR)
	{
		val = label_exist(data, param + 2, lbl_name);
		val = val * addr_diff(data, param + 2, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[3]);
		add_to_prog(data, ((unsigned char *)(&val))[2]);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param + 1);
		add_to_prog(data, ((unsigned char *)(&val))[3]);
		add_to_prog(data, ((unsigned char *)(&val))[2]);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
}

void	set_special(t_data *data, char *param, char *lbl_name,
		int inst_pos)
{
	int		val;

	if (param[1] == LABEL_CHAR)
	{
		val = label_exist(data, param + 2, lbl_name);
		val = val * addr_diff(data, param + 2, inst_pos);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
	else
	{
		val = ft_atoi(param + 1);
		add_to_prog(data, ((unsigned char *)(&val))[1]);
		add_to_prog(data, ((unsigned char *)(&val))[0]);
	}
}
