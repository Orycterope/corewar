/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 19:04:36 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 17:08:09 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"

static char	*sign_wrapper(char *str, t_conversion *conv)
{
	char	*out;

	if (ft_strchr("ouxXcsp", conv->conversion) != NULL)
		return (str);
	out = str;
	if (*str != '-')
	{
		if (ft_strchr(conv->flags, '+') != NULL)
			out = ft_strjoin("+", str);
		else if (ft_strchr(conv->flags, ' ') != NULL)
			out = ft_strjoin(" ", str);
		free(str);
	}
	return (out);
}

static char	*minus_wrapper(char *str, t_conversion *conv)
{
	size_t	length;
	char	*out;
	char	*old;

	out = str;
	length = ft_atoi(conv->width);
	if (length > 0)
		while (ft_strlen(out) < length)
		{
			old = out;
			out = ft_strjoin(old, " ");
			free(old);
		}
	return (out);
}

static char	*hash_wrapper(char *str, t_conversion *conv)
{
	char	*out;

	out = str;
	if (conv->conversion == 'o' && *out != '0')
	{
		out = ft_strjoin("0", str);
		free(str);
	}
	else if ((conv->conversion == 'x')
			|| conv->conversion == 'p')
	{
		out = ft_strjoin("0x", str);
		free(str);
	}
	else if (conv->conversion == 'X' && ft_atoi(str))
	{
		out = ft_strjoin("0X", str);
		free(str);
	}
	return (out);
}

char		*process_flags(char *str, t_conversion *conv)
{
	char	*out;

	if (str == NULL)
		str = ft_strdup("");
	out = str;
	if (ft_strchr(conv->flags, '+') != NULL
			|| ft_strchr(conv->flags, ' ') != NULL)
		out = sign_wrapper(out, conv);
	if (ft_strchr(conv->flags, '#') != NULL)
		out = hash_wrapper(out, conv);
	if (ft_strchr(conv->flags, '-') != NULL)
		out = minus_wrapper(out, conv);
	else if (ft_strchr(conv->flags, '0') != NULL
			&& (!(ft_strchr("diouxX", conv->conversion) && *(conv->precision))
			|| conv->conversion == 0))
		out = zero_wrapper(out, ft_atoi(conv->width));
	out = space_wrapper(out, ft_atoi(conv->width));
	return (out);
}
