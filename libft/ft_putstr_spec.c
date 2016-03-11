/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:31:23 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/05 15:07:14 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	ft_putstr_spec(char *s)
{
	char	*p;

	p = s;
	while (*p != '\0')
	{
		if (*p == '\xFF')
		{
			*p = '\0';
			ft_putstr(s);
			ft_putchar('\0');
			s = p + 1;
		}
		p++;
	}
	ft_putstr(s);
}
