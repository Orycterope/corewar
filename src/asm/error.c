/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 20:30:52 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/12 12:50:00 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/asm/asm.h"

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

void	error(char *err)
{
	ft_putendl(err);
	exit(1);
}

void	error_str(char *err, char *str)
{
	ft_putstr(err);
	ft_putendl(str);
	exit(1);
}

void	error_limit(char *err, char *str, char *str2, int limit)
{
	ft_putstr(err);
	ft_putstr(str);
	ft_putstr(str2);
	ft_putstr("(limit is ");
	ft_putnbr(limit);
	ft_putendl(")");
	exit(1);
}

void	error_third(char *err, char *str, char *str2)
{
	ft_putstr(err);
	ft_putstr(str);
	ft_putendl(str2);
	exit(1);
}
