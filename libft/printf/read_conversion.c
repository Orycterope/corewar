/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_conversion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 16:40:31 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 15:05:15 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read_conversion.h"
#include "get_conversion_parts.h"

t_conversion	*save_conversion_format(char *str)
{
	t_conversion	*conv;
	int				i;

	i = 1;
	if (!(conv = (t_conversion*)malloc(sizeof(t_conversion))))
		return (NULL);
	conv->conversion = 0;
	conv->flags = get_flags(&str[i]);
	i += ft_strlen(conv->flags);
	conv->width = get_width(&str[i]);
	i += ft_strlen(conv->width);
	conv->precision = get_precision(&str[i]);
	i += ft_strlen(conv->precision);
	conv->modifier = get_modifier(&str[i]);
	i += ft_strlen(conv->modifier);
	conv->conversion = get_conversion(&str[i]);
	conv->length = ++i;
	return (resolve_alias(conv));
}

void			free_conversion_format(t_conversion *conv)
{
	free(conv->flags);
	free(conv->width);
	free(conv->precision);
	free(conv->modifier);
	free(conv);
}
