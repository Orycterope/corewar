/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 21:14:30 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 16:15:14 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	write_verbose(t_data *data)
{
	if (data->verbose == 0)
		return ;
	ft_printf("\033[31;1m%s :\033[0m\n%s\n", NAME_CMD_STRING, data->name);
	ft_printf("\033[31;1m%s :\033[0m\n%s\n", COMMENT_CMD_STRING, data->comment);
	ft_printf("\033[31;1mSize of cor in bytes : \033[0m%d\n", data->prog_size);
	ft_printf("\033[31;1mProgram in hexadecimal : \033[0m");
	print_prog(data);
}

void	write_header(t_data *data)
{
	set_magic_to_cor(data);
	add_str_to_cor(data, data->name, PROG_NAME_LENGTH);
	add_to_cor(data, 0);
	add_to_cor(data, 0);
	add_to_cor(data, 0);
	add_to_cor(data, 0);
	add_to_cor(data, ((unsigned char *)(&data->prog_size))[3]);
	add_to_cor(data, ((unsigned char *)(&data->prog_size))[2]);
	add_to_cor(data, ((unsigned char *)(&data->prog_size))[1]);
	add_to_cor(data, ((unsigned char *)(&data->prog_size))[0]);
	add_str_to_cor(data, data->comment, COMMENT_LENGTH);
	add_to_cor(data, 0);
	add_to_cor(data, 0);
	add_to_cor(data, 0);
	add_to_cor(data, 0);
	add_str_to_cor(data, (char *)data->prog, data->prog_size);
	write_verbose(data);
	if (data->binary)
		return ;
	ft_putstr("Writing output program to ");
	ft_putendl(data->filename);
}
