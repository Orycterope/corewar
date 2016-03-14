/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   real_trim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 16:18:27 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/14 19:07:59 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_to_buf(char **buf, int *buf_len, char c)
{
	char	*tmp;
	int		i;
	int		len;

	*buf_len = *buf_len + 1;
	len = *buf_len;
	if ((tmp = (char *)malloc(sizeof(char) * len)) == NULL)
		error("Malloc error");
	i = 0;
	while (i < len - 1)
	{
		tmp[i] = (*buf)[i];
		i++;
	}
	tmp[i] = c;
	if (*buf != NULL)
		free(*buf);
	(*buf) = tmp;
}

int		next_word(char **buf, int *buf_len, char *str, int i)
{
	int		space;

	if (i == 0)
		space = 0;
	else
		space = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
	{
		if (space == 1)
			add_to_buf(buf, buf_len, ' ');
		space = 0;
		add_to_buf(buf, buf_len, str[i]);
		i++;
	}
	return (i);
}

char	*real_trim(char *str)
{
	int		i;
	int		buf_len;
	char	*buf;

	i = 0;
	buf_len = 0;
	buf = NULL;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\0')
		i = next_word(&buf, &buf_len, str, i);
	add_to_buf(&buf, &buf_len, '\0');
	return (buf);
}
