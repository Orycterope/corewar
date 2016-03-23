/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_cmt_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:04:13 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 17:04:22 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		add_newline_nm_cmt(char **s, char *add, unsigned int len)
{
	char	*join;
	char	*jointmp;

	if (ft_strlen(add) + 1 > len)
		return (-1);
	jointmp = ft_strjoin(*s, "\n");
	if (ft_strlen(add) != 0)
	{
		join = ft_strjoin(jointmp, add);
		ft_strcpy(*s, join);
		free(join);
	}
	else
	{
		ft_strcpy(*s, jointmp);
	}
	free(jointmp);
	return (1);
}

int		check_nm_cmt(t_data *data, char **s, int ind_len[], char *str)
{
	char	**arr;
	int		tmp;
	int		ret;

	tmp = is_in_str('"', str);
	if ((ret = 0) == 0 && tmp == 1)
	{
		arr = ft_strsplit(str, '"');
		if (arr[0] != 0 && (arr[1] == 0 ||
					(arr[1] + ft_strlen(arr[1])) == ft_pass_space_tab(arr[1])))
			ret = add_newline_nm_cmt(s, arr[0], ind_len[1]);
		else if (arr[0] == 0)
			ret = add_newline_nm_cmt(s, "", ind_len[1]);
		free_strsplit(arr);
		if (ret == -1)
			return (-1);
	}
	if (tmp == 0)
	{
		ret = add_newline_nm_cmt(s, str, ind_len[1]);
		if (ret == -1)
			return (-1);
		add_nm_cmt(data, s, ind_len[1] - (ft_strlen(str) + 1), ind_len[0]);
	}
	return (tmp);
}

void	add_nm_cmt(t_data *data, char **s, int len, int index)
{
	char	*str;
	int		ret;
	int		tmp[2];

	str = NULL;
	ret = 0;
	tmp[0] = index;
	tmp[1] = len;
	if (get_next_line(data->fd, &str) >= 0)
	{
		data->line++;
		ret = check_nm_cmt(data, s, tmp, str);
		if (ret == -1 && index == 1)
			error_line(data, ERR_TOO_LRG_NAME);
		else if (ret == -1)
			error_line(data, ERR_TOO_LRG_COM);
		if (ret >= 2 && index == 1)
			error_line(data, ERR_TOO_MNY_NAME);
		else if (ret >= 2)
			error_line(data, ERR_TOO_MNY_COMMENT);
		free(str);
	}
}

char	*name_comment(int index)
{
	if (index == 1)
		return (NAME_CMD_STRING);
	return (COMMENT_CMD_STRING);
}

int		name_comment_len(int index)
{
	if (index == 1)
		return (PROG_NAME_LENGTH);
	return (COMMENT_LENGTH);
}
