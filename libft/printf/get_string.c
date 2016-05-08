/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:45:35 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 17:17:46 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_string.h"

static int	check_escaped(char *str, int *length, char **end)
{
	if (str[1] == '%')
	{
		**end = '\0';
		*length += 1;
		*end += 2;
		return (1);
	}
	return (0);
}

char		*get_processed_str(char *str, va_list args, int *length, char **end)
{
	char			*processed_str;
	long long		argument;
	t_conversion	*conv;

	if (check_escaped(str, length, end))
		return (ft_strdup("%"));
	conv = save_conversion_format(str);
	if (!conv)
		return (NULL);
	if (conv->conversion != 0)
	{
		argument = get_arg(args, conv);
		processed_str = get_converted_string(argument, conv);
		processed_str = process_precision(processed_str, conv);
	}
	else
		processed_str = ft_tostr(*(*end + conv->length - 1));
	processed_str = process_flags(processed_str, conv);
	if (processed_str != NULL && ((**end = '\0') || 1))
	{
		*length += ft_strlen(processed_str);
		*end += conv->length;
	}
	free_conversion_format(conv);
	return (processed_str);
}
