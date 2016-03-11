/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 14:56:18 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 15:07:45 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utf.h"

char		*convert_utf_string(wint_t *endpoints_list)
{
	char		*out;
	char		*old;
	char		*new;
	long long	utf;

	if (*endpoints_list == '\0')
		return (ft_strdup(""));
	out = NULL;
	while (*endpoints_list != (wint_t)0)
	{
		old = out;
		utf = convert_utf(*endpoints_list);
		new = ft_strnew(sizeof(long long) + 1);
		ft_memcpy(new, &utf, sizeof(long long));
		out = ft_strjoin(old, ft_strrev(new));
		free(old);
		free(new);
		endpoints_list++;
	}
	return (out);
}

long long	convert_utf(wint_t arg)
{
	unsigned char		power;
	int					rang;
	unsigned long long	out;

	if (arg <= 0x7F)
		return (arg);
	power = 0x3F;
	rang = 0;
	out = 0;
	while (arg > (wint_t)power)
	{
		out += (long long)((arg & 0x3F) | 0x80) << (rang++ * 8);
		power /= 2;
		arg >>= 6;
	}
	out += (long long)((unsigned char)(~power << 1) | arg) << (rang * 8);
	return (out);
}
