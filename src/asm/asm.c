/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:38:06 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 16:10:45 by jriallan         ###   ########.fr       */
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

void	run(t_data *data, char *filename)
{
	char	*tmp;
	init_data(data);
	if (filename != NULL)
	{
		set_filename(data, filename);
		data->fd = open(filename, O_RDONLY);
	}
	else
	{
		ft_printf("\t\t\033[32;1;4mLive Coding Mode\033[0m\n");
		while (filename == NULL || ft_strcmp(filename, "") == 0)
		{
			ft_printf("\033[36;1mEnter filename :\033[0m\n");
			get_next_line(0, &filename);
		}
		tmp = ft_strjoin(filename,".s");
		free(filename);
		set_filename(data, tmp);
		free(tmp);
		ft_printf("\033[36;1mWrite your file here :\033[0m\n");
		data->fd = 0;
	}
	if (data->fd < 0)
		error("Open fail");
	parser(data);
	build(data);
	write_header(data);
	write_file(data);
	free_data(data);
}

int		main(int argc, char *argv[])
{
	t_data	data;
	int		i;

	i = 1;
	data.verbose = 0;
	data.binary = 0;
	while (i < argc)
	{
		if (ft_strcmp(argv[i], "-v") == 0 && ++i > 0)
			data.verbose = 1;
		if (ft_strcmp(argv[i], "-b") == 0 && ++i > 0)
			data.binary = 1;
		if (ft_strcmp(argv[i], "-b") == 0 || ft_strcmp(argv[i], "-v") == 0)
			continue ;
		if (ft_strcmp(argv[i], "-l") == 0)
			run(&data, NULL);
		else
			run(&data, argv[i]);
		i++;
	}
	usage(argc, argv);
	return (0);
}
