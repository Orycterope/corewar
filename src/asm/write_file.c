/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 21:14:30 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/17 12:03:59 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

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
	ft_putstr("Writing output program to ");
	ft_putendl(data->filename);
}
