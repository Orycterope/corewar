/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 17:45:48 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/18 20:06:33 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	add_to_prog(t_data *data, unsigned char c)
{
	unsigned char	*tmp;
	int				i;

	data->prog_size++;
	if ((tmp = (unsigned char *)malloc(sizeof(unsigned char) *
				data->prog_size)) == NULL)
		error("Malloc error");
	i = 0;
	while (i < data->prog_size - 1)
	{
		tmp[i] = data->prog[i];
		i++;
	}
	tmp[i] = c;
	free(data->prog);
	data->prog = tmp;
}	

void	print_prog(t_data *data)
{
	int		i;

	i = 0;
	while (i < data->prog_size)
	{
		ft_printf("%x ", data->prog[i]);
		if (i % 10 == 0 && i != 0)
			ft_putendl("");
		i++;
	}
}
