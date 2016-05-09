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
	ft_putendl_fd(err, 2);
	ft_putstr_fd(" [", 2);
	ft_putnbr_fd(line, 2);
	ft_putstr_fd(":", 2);
	ft_putnbr_fd(column, 2);
	ft_putstr_fd("]", 2);
	exit(1);
}

void	error_line(t_data *data, char *err)
{
	if (data != NULL)
	{
		ft_putstr_fd("Error line ", 2);
		ft_putnbr_fd(data->line, 2);
		ft_putstr_fd(" : ", 2);
	}
	ft_putendl_fd(err, 2);
	exit(1);
}

void	error(char *err)
{
	ft_putendl_fd(err, 2);
	exit(1);
}

void	error_str(t_data *data, char *err, char *str)
{
	if (data != NULL)
	{
		ft_putstr_fd("Error line ", 2);
		ft_putnbr_fd(data->line, 2);
		ft_putstr_fd(" : ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putendl_fd(str, 2);
	exit(1);
}

void	error_limit(t_data *data, char *err, char *str, int limit)
{
	if (data != NULL)
	{
		ft_putstr_fd("Error line ", 2);
		ft_putnbr_fd(data->line, 2);
		ft_putstr_fd(" : ", 2);
	}
	ft_putstr_fd(err, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" (limit is ", 2);
	ft_putnbr_fd(limit, 2);
	ft_putendl_fd(")", 2);
	exit(1);
}
