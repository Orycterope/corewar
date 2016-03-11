/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converter.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 19:02:28 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 14:57:57 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "converter.h"

static char	*convert_decimals(long long arg, t_conversion *conv)
{
	char	op;

	op = conv->conversion;
	if (op == 'd' || op == 'i' || op == 'D')
		return (itoa(arg));
	else if (op == 'u' || op == 'U')
		return (itoa_base(arg, "0123456789"));
	else if (op == 'o' || op == 'O')
		return (itoa_base(arg, "01234567"));
	else if (op == 'x' || op == 'p')
		return (itoa_base(arg, "0123456789abcdef"));
	else if (op == 'X')
		return (itoa_base(arg, "0123456789ABCDEF"));
	return (NULL);
}

static char	*convert_chars(long long arg, t_conversion *conv)
{
	char	*out;
	size_t	length;

	if (arg >= 0x80000000)
		return (NULL);
	if (arg == 0)
		return (ft_strdup("\xFF"));
	length = 1;
	if (ft_strchr(conv->modifier, 'l'))
	{
		length = sizeof(long long);
		arg = convert_utf(arg);
	}
	out = ft_strnew(length + 1);
	ft_memcpy(out, &arg, length);
	ft_strrev(out);
	return (out);
}

static char	*convert_strings(long long arg, t_conversion *conv)
{
	char	op;

	op = conv->conversion;
	if (op == 's')
	{
		if ((char *)arg == NULL)
			return (ft_strdup("(null)"));
		if (ft_strchr(conv->modifier, 'l'))
			return (convert_utf_string((wint_t *)arg));
		return (ft_strdup((char *)arg));
	}
	return (NULL);
}

char		*get_converted_string(long long arg, t_conversion *conv)
{
	if (ft_strchr("dDioOuUxXp", conv->conversion) != NULL)
		return (convert_decimals(arg, conv));
	else if (ft_strchr("s", conv->conversion) != NULL)
		return (convert_strings(arg, conv));
	else if (ft_strchr("cC", conv->conversion) != NULL)
		return (convert_chars(arg, conv));
	return (NULL);
}
