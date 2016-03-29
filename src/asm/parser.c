/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:59:26 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/29 10:32:13 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		read_name_comment(t_data *data, char *str)
{
	int		ret;

	ret = 0;
	if ((ret = parse_nm_cmt(data, &data->name, str, 1)) == 0)
		ret = parse_nm_cmt(data, &data->comment, str, 2);
	return (ret);
}

int		is_comment(char *str)
{
	int		ret;

	str = rm_char(str, " \t");
	ret = 0;
	if (ft_strcmp(str, "") == 0)
		ret = 1;
	else if (str[0] == COMMENT_CHAR)
		ret = 1;
	free(str);
	return (ret);
}

int		chk_after_lbl(char *buf, char **next)
{
	int		i;

	i = 0;
	while (buf[i] != '\0' && buf[i] != LABEL_CHAR)
	{
		i++;
	}
	if (buf[i] == LABEL_CHAR)
	{
		buf = ft_pass_space_tab(buf + i + 1);
		if (ft_strlen(buf) > 0)
		{
			*next = ft_strdup(buf);
			return (1);
		}
	}
	return (0);
}

int		routes(t_data *data, char *buf)
{
	char		*next;

	if (is_comment(buf))
		;
	else if (read_name_comment(data, buf))
		;
	else if (check_add_lbl(buf, data))
	{
		next = NULL;
		if (chk_after_lbl(buf, &next))
			check_add_instruc(next, data);
		if (next != NULL)
			free(next);
	}
	else if (check_add_instruc(buf, data))
		;
	else if (data->fd == 0 && ft_strcmp(buf, "save") == 0)
		return (0);
	else
		error_line(data, "Lexical error");
	return (1);
}

void	parser(t_data *data)
{
	char		*buf;
	int			next;

	next = 1;
	while (next && (buf = NULL) == NULL && get_next_line(data->fd, &buf) > 0)
	{
		next = routes(data, buf);
		free(buf);
		data->line++;
	}
	if (data->name == NULL)
		error_str(NULL, "Error : missing ", NAME_CMD_STRING);
	if (data->comment == NULL)
		error_str(NULL, "Error : missing ", COMMENT_CMD_STRING);
}
