/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:59:26 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/17 12:46:44 by rporcon          ###   ########.fr       */
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
	if (tmp == 1)
	{
		arr = ft_strsplit(str, '"');
		if (arr[1] == 0 ||
				(arr[1] + ft_strlen(arr[1])) == ft_pass_space_tab(arr[1]))
		{
			ret = add_newline_nm_cmt(s, arr[0], ind_len[1]);
			free_strsplit(arr);
			if (ret == -1)
				return (-1);
		}
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

int		check_quote_nm_cmt(t_data *data, char *str, char *cmd)
{
	int cont;

	cont = 0;
	if ((cont = is_in_str('"', str)) == 2 || cont == 1)
		return (cont);
	else
		error_str(data, "to many '\"' in ", cmd);
	return (-1);
}

int		nm_cmt(t_data *data, char **s, char **arr, int index)
{
	unsigned int	len;

	len = name_comment_len(index);
	if (arr[2] == 0 ||
			(arr[2] + ft_strlen(arr[2])) == ft_pass_space_tab(arr[2]))
	{
		if (*s != NULL && index == 1)
			error_line(data, ERR_ALRD_SET_NAME);
		else if (*s != NULL)
			error_line(data, ERR_ALRD_SET_COMMENT);
		if (ft_strlen(arr[1]) > len && index == 1)
			error_limit(data, ERR_LENGTH_NAME, NULL, len);
		else if (ft_strlen(arr[1]) > len)
			error_limit(data, ERR_LENGTH_COM, NULL, len);
		if ((*s = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
			error("Malloc error");
		ft_bzero(*s, len + 1);
		ft_strcpy(*s, arr[1]);
	}
	else if (index == 1)
		error_line(data, ERR_LFT_QUOTE_NAME);
	else
		error_line(data, ERR_LFT_QUOTE_COMMENT);
	return (1);
}

int		parse_nm_cmt(t_data *data, char **s, char *str, int index)
{
	int				ret;
	int				cont;
	unsigned int	len;
	char			**arr;
	char			*cmd;

	ret = 0;
	len = name_comment_len(index);
	cmd = name_comment(index);
	str = ft_pass_space_tab(str);
	if (ft_strncmp(str, cmd, ft_strlen(cmd)) == 0 &&
			*ft_pass_space_tab(str + ft_strlen(cmd)) == '\"')
	{
		cont = check_quote_nm_cmt(data, str, cmd);
		arr = ft_strsplit(str, '"');
		ret = nm_cmt(data, s, arr, index);
		if (cont == 1)
			add_nm_cmt(data, s, len - ft_strlen(arr[1]), index);
		free_strsplit(arr);
	}
	else if (ft_strncmp(str, cmd, ft_strlen(cmd)) == 0 &&
			*ft_pass_space_tab(str + ft_strlen(cmd)) != '\"')
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

void	parser(t_data *data)
{
	char		*buf;
	t_label		*lbl_lst;
	t_instruc	*inst_lst;

	buf = NULL;
	lbl_lst = NULL;
	inst_lst = NULL;
	while (get_next_line(data->fd, &buf) > 0)
	{
		if (is_comment(buf))
			ft_putendl("[IS COMMENT]");
		else if (read_name_comment(data, buf))
			ft_putendl("[NAME || COMMENT]");
		else if (check_add_lbl(buf, lbl_lst, data))
			ft_putendl("[LBL]");
		else if (check_add_instruc(buf, lbl_lst, &inst_lst, data))
			ft_putendl("[INSTRUC]");
		else
			error_line(data, "lexical error");
		free(buf);
		data->line++;
	}
	if (data->name == NULL)
		error_str(NULL, "Error : missing ", NAME_CMD_STRING);
	if (data->comment == NULL)
		error_str(NULL, "Error : missing ", COMMENT_CMD_STRING);
}
