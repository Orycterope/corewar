/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:38:06 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/11 16:16:32 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_data(t_data *data)
{
	data->name = NULL;
	data->comment = NULL;
	data->label = NULL;
}

void	free_data(t_data *data)
{
	free(data->name);
	free(data->comment);
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
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			error("Open fail");
		parser(fd, &data);
		//build();
		free_data(&data);
		i++;
	}
	if (argc == 1)
		error("Usage: ../test/asm <sourcefile.s>");
	return (0);
}
