/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 18:59:26 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/11 19:45:58 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_in_str(char c, char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*rem_char(char *str, char *rem)
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
	while (str[j] == '\0')
	{
		if (is_in_str(str[j], rem) == 0)
			ret[i++] = str[j];
		j++;
	}
	return (ret);
}

void	read_name_comment(t_data *data, char *str)
{
	if (data->name == NULL &&
			ft_strncmp(NAME_CMD_STRING, str, ft_strlen(NAME_CMD_STRING)))
	{
		PROG_NAME_LENGTH;
	}
	if (data->comment == NULL &&
			ft_strncmp(COMMENT_CMD_STRING, str, ft_strlen(COMMENT_CMD_STRING)))
	{
		COMMENT_LENGTH;
	}
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
