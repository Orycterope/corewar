/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 19:58:54 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 14:47:54 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cast.h"

static long long	d_types(va_list args, t_conversion *conv)
{
	if (*(conv->modifier) == 'h')
	{
		if (*(conv->modifier + 1) == 'h')
			return ((long long)((signed char)va_arg(args, int)));
		else
			return ((long long)((short)va_arg(args, int)));
	}
	else if (*(conv->modifier) == 'l')
	{
		if (*(conv->modifier + 1) == 'l')
			return ((long long)va_arg(args, long long));
		else
			return ((long long)va_arg(args, long));
	}
	else if (*(conv->modifier) == 'j')
		return ((long long)va_arg(args, intmax_t));
	else if (*(conv->modifier) == 'z')
		return ((long long)va_arg(args, size_t));
	else
		return ((long long)va_arg(args, int));
}

static long long	o_types(va_list args, t_conversion *conv)
{
	if (*(conv->modifier) == 'h')
	{
		if (*(conv->modifier + 1) == 'h')
			return ((long long)((unsigned char)va_arg(args, int)));
		else
			return ((long long)((unsigned short)va_arg(args, int)));
	}
	else if (*(conv->modifier) == 'l')
	{
		if (*(conv->modifier + 1) == 'l')
			return ((long long)va_arg(args, unsigned long long));
		else
			return ((long long)va_arg(args, unsigned long));
	}
	else if (*(conv->modifier) == 'j')
		return ((long long)va_arg(args, uintmax_t));
	else if (*(conv->modifier) == 'z')
		return ((long long)va_arg(args, size_t));
	else
		return ((long long)va_arg(args, unsigned));
}

static long long	c_types(va_list args, t_conversion *conv)
{
	if ((conv->conversion == 'c' && *(conv->modifier) == 'l')
			|| conv->conversion == 'C')
		return ((long long)va_arg(args, wint_t));
	else if (conv->conversion == 'c')
		return ((long long)va_arg(args, int));
	else if ((conv->conversion == 's' && *(conv->modifier) == 'l')
			|| conv->conversion == 'S')
		return ((long long)va_arg(args, wchar_t*));
	else if (conv->conversion == 's')
		return ((long long)va_arg(args, char*));
	else if (conv->conversion == 'p')
		return ((long long)va_arg(args, int*));
	else
		return ((long long)va_arg(args, int));
}

long long			get_arg(va_list args, t_conversion *conv)
{
	if (ft_strchr("DOU", conv->conversion) != NULL)
		return ((long long)va_arg(args, long int));
	if (ft_strchr("di", conv->conversion) != NULL)
		return (d_types(args, conv));
	else if (ft_strchr("ouxX", conv->conversion) != NULL)
		return (o_types(args, conv));
	else if (ft_strchr("cCsSp", conv->conversion) != NULL)
		return (c_types(args, conv));
	return (0);
}
