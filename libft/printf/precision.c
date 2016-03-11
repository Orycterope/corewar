/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 18:57:09 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 19:52:17 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "precision.h"

char		*process_precision(char *str, t_conversion *conv)
{
	char	*out;
	char	*old;
	size_t	precision;

	out = str;
	if (*(conv->precision++) == '.')
	{
		precision = ft_atoi(conv->precision);
		if (ft_strchr("diouxXp", conv->conversion)
			&& ft_atoi(str) == 0 && precision == 0)
			*str = '\0';
		else if (ft_strchr("diouxXp", conv->conversion) != NULL)
			out = zero_wrapper(out, precision + (ft_strchr(str, '-') != NULL));
		else if (conv->conversion == 's')
		{
			old = out;
			out = ft_strsub(out, 0, precision);
			free(old);
		}
	}
	conv->precision--;
	return (out);
}
