/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:59:26 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/14 16:52:48 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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

char	*ft_pass_space_tab(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && (str[index] == ' ' || str[index] == '\t'))
		index++;
	return (str + index);
}

int		parse_nm_cmt(t_data *data, char **s, char *str, int index)
{
	int				ret;
	unsigned int	len;
	char			**arr;
	char			*cmd;

	ret = 0;
	len = name_comment_len(index);
	cmd = name_comment(index);
	str	= ft_pass_space_tab(str);
	if (ft_strncmp(str, cmd, ft_strlen(cmd)) == 0 && *ft_pass_space_tab(str + ft_strlen(cmd)) == '\"')
	{
		if (is_in_str('"', str) == 2)
		{
			arr = ft_strsplit(str, '"');
			if (arr[2] == 0 || (arr[2] + ft_strlen(arr[2])) == ft_pass_space_tab(arr[2]))
			{
				if (*s != NULL)
					error_str(data, cmd, " is already set");
				if (ft_strlen(arr[1]) > len)
					error_limit(data, "length of string is too large in ", cmd, len);
				if ((*s = (char *)malloc(sizeof(char) * len)) == NULL)
					error("Malloc error");
				ft_bzero(*s, len);
				ft_strcpy(*s, arr[1]);
				ret = 1;
			}
			else
				error_str(data, "character after '\"' in ", cmd);
			free_strsplit(arr);
		}
		else
			error_str(data, "to many '\"' in ", cmd);
	}
	else if (ft_strncmp(str, cmd, ft_strlen(cmd)) == 0 && *ft_pass_space_tab(str + ft_strlen(cmd)) != '\"')
		error_str(data, "character between '\"' and ", cmd);
	return (ret);
}

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

void	parser(int fd, t_data *data)
{
	char		*buf;
	t_label		*lbl_lst;
	t_instruc	*inst_lst;

	buf = NULL;
	lbl_lst = NULL;
	inst_lst = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		if (is_comment(buf))
		{
			ft_putendl("com");
		}
		if (read_name_comment(data, buf))
		{
			ft_putendl("name or comment");
		}
		check_add_lbl(buf, lbl_lst, data);
		check_add_instruc(buf, lbl_lst, inst_lst, data);
		free(buf);
		data->line++;
	}
	if (data->name == NULL)
		error_str(NULL, "Error : missing ", NAME_CMD_STRING);
	if (data->comment == NULL)
		error_str(NULL, "Error : missing ", COMMENT_CMD_STRING);
}
