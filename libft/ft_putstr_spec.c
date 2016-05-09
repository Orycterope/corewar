/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_spec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 12:31:23 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/09 18:09:38 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

void	ft_putstr_spec_fd(char *s, int fd)
{
	char	*p;

	p = s;
	while (*p != '\0')
	{
		if (*p == '\xFF')
		{
			*p = '\0';
			ft_putstr_fd(s, fd);
			ft_putchar_fd('\0', fd);
			s = p + 1;
		}
		p++;
	}
	ft_putstr_fd(s, fd);
}
