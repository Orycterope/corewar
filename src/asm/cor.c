/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cor.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 20:31:56 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/29 10:18:07 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_to_cor(t_data *data, char c)
{
	char	*tmp;
	int		i;

	data->cor_len++;
	if ((tmp = (char *)malloc(sizeof(char) * data->cor_len)) == NULL)
		error("Malloc error");
	i = 0;
	while (i < data->cor_len - 1)
	{
		tmp[i] = data->cor[i];
		i++;
	}
	tmp[i] = c;
	free(data->cor);
	data->cor = tmp;
}

void	add_str_to_cor(t_data *data, char *str, int len)
{
	char	*tmp;
	int		i;
	int		j;

	data->cor_len += len;
	if ((tmp = (char *)malloc(sizeof(char) * data->cor_len)) == NULL)
		error("Malloc error");
	i = 0;
	while (i < data->cor_len - len)
	{
		tmp[i] = data->cor[i];
		i++;
	}
	j = 0;
	while (j < len)
	{
		tmp[i] = str[j];
		i++;
		j++;
	}
	free(data->cor);
	data->cor = tmp;
}

void	set_filename(t_data *data, char *name)
{
	int		i;
	int		ext;
	char	*tmp;

	ext = 0;
	i = 0;
	while (name[i] != '\0')
	{
		if (++ext >= 0 && name[i++] == '.')
			ext = 0;
	}
	ext = i - ext;
	if ((tmp = (char *)malloc(sizeof(char) * (ext + 4))) == NULL)
		error("Malloc error");
	i = 0;
	while (name[i] != '\0' && i < ext)
	{
		tmp[i] = name[i];
		i++;
	}
	tmp[i++] = 'c';
	tmp[i++] = 'o';
	tmp[i++] = 'r';
	tmp[i++] = '\0';
	data->filename = tmp;
}

void	set_magic_to_cor(t_data *data)
{
	int		magic;

	magic = COREWAR_EXEC_MAGIC;
	add_to_cor(data, ((unsigned char *)(&magic))[3]);
	add_to_cor(data, ((unsigned char *)(&magic))[2]);
	add_to_cor(data, ((unsigned char *)(&magic))[1]);
	add_to_cor(data, ((unsigned char *)(&magic))[0]);
}

void	write_file(t_data *data)
{
	int		fd;

	if (data->binary)
	{
		write(1, data->cor, data->cor_len);
	}
	else
	{
		fd = open(data->filename, O_WRONLY | O_CREAT | O_TRUNC,
															S_IRUSR | S_IWUSR);
		if (fd < 0)
			error("Open fail");
		write(fd, data->cor, data->cor_len);
	}
}
