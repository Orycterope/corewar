/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 10:27:43 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 14:59:55 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	get_next_precent_position(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0' && str[i] != '%')
		i++;
	return (i);
}

static int	manage_error(char *insert, char **str, int position)
{
	if (insert == NULL)
	{
		(*str)[position] = '\0';
		free(insert);
		return (1);
	}
	return (0);
}

static int	replace_conversion(char **str, va_list args)
{
	char	*s2;
	char	*old1;
	char	*old2;
	char	*insert;
	int		i;

	*str = ft_strdup(*str);
	i = get_next_precent_position(*str);
	while ((*str)[i] != '\0')
	{
		old1 = *str;
		s2 = &((*str)[i]);
		insert = get_processed_str(s2, args, &i, &s2);
		if (manage_error(insert, str, i))
			return (1);
		old2 = ft_strjoin(*str, insert);
		free(insert);
		*str = ft_strjoin(old2, s2);
		free(old1);
		free(old2);
		i += get_next_precent_position(&((*str)[i]));
	}
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list args;
	int		count;
	int		error;

	va_start(args, format);
	error = replace_conversion((char **)&format, args);
	if (error)
		count = -1;
	else
		count = ft_strlen(format);
	ft_putstr_spec((char *)format);
	free((void*)format);
	va_end(args);
	return (count);
}
