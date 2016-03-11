/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:38:06 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/11 18:06:49 by jriallan         ###   ########.fr       */
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

void	init_data(t_data *data)
{
	data->filename = NULL;
	data->name = NULL;
	data->comment = NULL;
	data->cor = NULL;
	data->cor_len = 0;
	data->label = NULL;
}

void	free_data(t_data *data)
{
	free(data->filename);
	free(data->name);
	free(data->comment);
	free(data->cor);
	//free all label
	//data->label;
}

void	set_filename(t_data *data, char *name)
{
	int		i;
	int		ext;
	char	*tmp;

	i = 0;
	while (name[i] != '\0')
	{
		ext++;
		if (name[i++] == '.')
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

void	set_magic_to_cor(t_data	*data)
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

	fd = open(data->filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	if (fd < 0)
		error("Open fail");
	write(fd, data->cor, data->cor_len);
}

int		main(int argc, char *argv[])
{
	t_data	data;
	int		fd;
	int		i;

	i = 1;
	while (i < argc)
	{
		init_data(&data);
		set_filename(&data, argv[i]);
		set_magic_to_cor(&data);
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			error("Open fail");
		parser(fd, &data);
		//build();
		write_file(&data);
		free_data(&data);
		i++;
	}
	if (argc == 1)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		error(" <sourcefile.s>");
	}
	return (0);
}
