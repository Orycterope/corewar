/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conversion_parts.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 13:27:20 by tvermeil          #+#    #+#             */
/*   Updated: 2015/12/28 18:26:51 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_conversion_parts.h"

char			*get_flags(char *str)
{
	int		i;

	i = 0;
	while (str[i] == '#' || str[i] == '0' || str[i] == '-' || str[i] == '+'
			|| str[i] == ' ')
		i++;
	return (ft_strsub(str, 0, i));
}

char			*get_width(char *str)
{
	int		i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	return (ft_strsub(str, 0, i));
}

char			*get_precision(char *str)
{
	int		i;

	i = 0;
	if (*str == '.')
		i++;
	while (i > 0 && str[i] >= '0' && str[i] <= '9')
		i++;
	return (ft_strsub(str, 0, i));
}

char			*get_modifier(char *str)
{
	int		i;

	i = 0;
	if ((*str == 'h' && *(str + 1) == 'h')
			|| (*str == 'l' && *(str + 1) == 'l'))
		i = 2;
	else if (*str == 'h' || *str == 'l' || *str == 'j' || *str == 'z')
		i = 1;
	return (ft_strsub(str, 0, i));
}

char			get_conversion(char *str)
{
	char	*conversion_chars;

	conversion_chars = "sSpdDioOuUxXcC";
	if (ft_strchr(conversion_chars, *str) != NULL)
		return (*str);
	return (0);
}
