/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:38:06 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/22 18:38:38 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_data(t_data *data)
{
	data->filename = NULL;
	data->name = NULL;
	data->comment = NULL;
	data->cor = NULL;
	data->cor_len = 0;
	data->label = NULL;
	data->line = 1;
	data->prog_size = 0;
}

void	free_data(t_data *data)
{
	free(data->filename);
	free(data->name);
	free(data->comment);
	free(data->cor);
	free_inst_lbl(data->label);
}

void	usage(int argc, char *argv[])
{
	if (argc == 1)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putendl(" <sourcefile.s>");
	}
}

int		main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	i = 1;
	while (i < argc)
	{
		init_data(&data);
		set_filename(&data, argv[i]);
		data.fd = open(argv[i], O_RDONLY);
		if (data.fd < 0)
			error("Open fail");
		parser(&data);
		build(&data);
		write_header(&data);
		write_file(&data);
		free_data(&data);
		i++;
	}
	usage(argc, argv);
	return (0);
}
