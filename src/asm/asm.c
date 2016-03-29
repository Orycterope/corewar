/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 19:38:06 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/29 10:29:01 by rporcon          ###   ########.fr       */
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
	if (argc != 1)
		return ;
	ft_putstr("Usage : ");
	ft_putstr(argv[0]);
	ft_putendl(" [-v|-l|-b] <sourcefile.s>");
	ft_putendl("\t-v : verbose mode, write data and program in hexadecimal.");
	ft_printf("\t-l : live coding mode, you can write %s",
											"directly your s file manualy.\n");
	ft_printf("\t-b : binary mode, return your binary file %s",
													"in standard output.\n");
}

void	run(t_data *data, char *filename)
{
	init_data(data);
	if (filename != NULL)
	{
		set_filename(data, filename);
		data->fd = open(filename, O_RDONLY);
	}
	else
		live_coding_mode(data, filename);
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

	essential_char_in_label_chars();
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
