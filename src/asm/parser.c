/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:59:26 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/11 22:09:57 by jriallan         ###   ########.fr       */
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
	ft_putnbr(len);
	if ((ret = (char *)malloc(sizeof(char) * ++len)) == NULL)
		error("Malloc error");
	ft_bzero(ret, len);
	i = 0;
	j = 0;
	while (str[j] == '\0')
	{
		if (is_in_str(str[j], rem) != 0)
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

int		read_name_comment(t_data *data, char *str)
{
	char	*tmp;
	char	**arr;
	char	*str2;
	int		len;
	int		ret;

	ret = 0;
	if (is_in_str('"', str) == 2)
	{
		arr = ft_strsplit(str, '"');
		str2 = rm_char(arr[0], " \t");
	ft_putstr(NAME_CMD_STRING);
	ft_putendl(";");
	ft_putstr(str2);
	ft_putendl(";");
	ft_putnbr(ft_strlen(NAME_CMD_STRING));
		if (data->name == NULL &&
			ft_strncmp(NAME_CMD_STRING, str2, ft_strlen(NAME_CMD_STRING)) == 0)
		{
	ft_putendl("plop");
			len = PROG_NAME_LENGTH + 1;
			if (arr[2] == 0 || arr[3] == 0)
			{
	ft_putendl("pop");
				if ((tmp = (char *)malloc(sizeof(char) * len)) == NULL)
					error("Malloc error");
				data->name = ft_strdup(arr[1]);
				ft_putendl(data->name);
				ret = 1;
			}
			else
				error("Error : character after \" in name");
		}
		if (data->comment == NULL &&
				ft_strncmp(COMMENT_CMD_STRING, str2, ft_strlen(COMMENT_CMD_STRING)) == 0)
		{
			//COMMENT_LENGTH;
			ret = 1;
		}
		free_strsplit(arr);
		free(str2);
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
