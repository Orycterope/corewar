/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:38:06 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/10 20:59:29 by jriallan         ###   ########.fr       */
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

	i = 0;
	while (str[i] != '\0')
	{
		ext++;
		if (str[i] == '.')
			ext = 0;
		i++;
	}
	ext = i - ext;
	if ((ret = (char *)malloc(sizeof(char) * (ext + 4))) == NULL)
		error("Malloc error");
	i = 0;
	while (str[i] != '\0' && i < ext)
	{
		if (str[i] == '.')
			ext = 0;
		ext++;
		i++;
	}
	str[i++] = 'c';
	str[i++] = 'o';
	str[i++] = 'r';
	str[i++] = '\0';
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
		set_filename(argv[i]);
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
			error("Open fail");
		parser(fd, &data);
		//build();
		free_data(&data);
		i++;
	}
	return (0);
}
