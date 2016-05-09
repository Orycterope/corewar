/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:30:52 by jriallan          #+#    #+#             */
/*   Updated: 2016/05/09 13:54:01 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	error_at(char *err, int line, int column)
{
	ft_putendl(err);
	ft_putstr(" [");
	ft_putnbr(line);
	ft_putstr(":");
	ft_putnbr(column);
	ft_putstr("]");
	exit(1);
}

void	error_line(t_data *data, char *err)
{
	if (data != NULL)
	{
		ft_putstr("Error line ");
		ft_putnbr(data->line);
		ft_putstr(" : ");
	}
	ft_putendl(err);
	exit(1);
}

void	error(char *err)
{
	ft_putendl(err);
	exit(1);
}

void	error_str(t_data *data, char *err, char *str)
{
	if (data != NULL)
	{
		ft_putstr("Error line ");
		ft_putnbr(data->line);
		ft_putstr(" : ");
	}
	ft_putstr(err);
	ft_putendl(str);
	exit(1);
}

void	error_limit(t_data *data, char *err, char *str, int limit)
{
	if (data != NULL)
	{
		ft_putstr("Error line ");
		ft_putnbr(data->line);
		ft_putstr(" : ");
	}
	ft_putstr(err);
	ft_putstr(str);
	ft_putstr(" (limit is ");
	ft_putnbr(limit);
	ft_putendl(")");
	exit(1);
}
