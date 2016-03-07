/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 12:51:08 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:50:49 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isignored(const char c)
{
	return (c == ' ' || c == '\n' || c == '\v' || c == '\t'
			|| c == '\r' || c == '\f');
}

int			ft_atoi(const char *str)
{
	int	value;
	int	is_neg;

	value = 0;
	is_neg = 1;
	while (ft_isignored(*str))
		str++;
	if (*str == '-' || *str == '+')
		is_neg = (*str++ == '+') ? 1 : -1;
	while (ft_isdigit(*str))
		value = value * 10 + (*str++ - '0');
	return (value * is_neg);
}
