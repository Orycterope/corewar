/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:59:26 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/12 00:09:40 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_in_str(char c, char *str)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			ret++;
		i++;
	}
	return (ret);
}

char	*rm_char(char *str, char *rem)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_in_str(str[i], rem) == 0)
			len++;
		i++;
	}
	if ((ret = (char *)malloc(sizeof(char) * ++len)) == NULL)
		error("Malloc error");
	ft_bzero(ret, len);
	i = 0;
	j = 0;
	while (str[j] != '\0')
	{
		if (is_in_str(str[j], rem) == 0)
			ret[i++] = str[j];
		j++;
	}
	return (ret);
}

void	free_strsplit(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] == 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int		parse_nm_cmt(t_data *data, char *str, char *cmd, unsigned int length)
{
	int		ret;
	char	**arr;
	char	*str2;
	char	*tmp;
	int		len;

	ret = 0;
	arr = ft_strsplit(str, '"');
	str2 = rm_char(arr[0], " \t");
	ft_putendl(cmd);
	ft_putendl(str2);
	if (data->name == NULL && //ft_strncmp(cmd, str2, strlen(str2)) == 0 &&
												ft_strcmp(cmd, str2) == 0)
	{
		len = length + 1;
		if (arr[2] == 0)
		{
			if (ft_strlen(str) > length)
				error_limit("Error : length of \"", cmd,
						"\" is too large (limit is ", length);
			if ((tmp = (char *)malloc(sizeof(char) * len)) == NULL)
				error("Malloc error");
			if () TODO
			data->name = ft_strdup(arr[1]);
			data->name = ft_strdup(arr[1]);
			ft_putendl(data->name);
			ret = 1;
		}
		else
			error_str("Error : character after '\"' in ", cmd);
	}
	else if (data->name != NULL && ft_strcmp(cmd, str2) == 0)
		error_third("Error : ", cmd, " is already set");
	else if (data->name == NULL && ft_strcmp(cmd, str2) == 0 && ft_strncmp(cmd, str2, ft_strlen(str2)) != 0)
		error_str("Error : character before '\"' in ", cmd);
	free_strsplit(arr);
	free(str2);
	return (ret);
}

int		read_name_comment(t_data *data, char *str)
{
	int		ret;

	ret = 0;
	if (is_in_str('"', str) == 2)
	{
		ret = parse_nm_cmt(data, str, NAME_CMD_STRING, PROG_NAME_LENGTH);
		ret = parse_nm_cmt(data, str, COMMENT_CMD_STRING, COMMENT_LENGTH);
//		if (data->comment == NULL &&
//				ft_strncmp(COMMENT_CMD_STRING, str2, ft_strlen(COMMENT_CMD_STRING)) == 0)
//		{
			//COMMENT_LENGTH;
//			ret = 1;
//		}
	}
	return (ret);
}

void	parser(int fd, t_data *data)
{
	char	*buf;

	buf = NULL;
	while (get_next_line(fd, &buf) > 0)
	{
		read_name_comment(data, buf);
		free(buf);
	}
}
