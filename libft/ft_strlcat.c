/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:41:11 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:06:49 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*s;
	char	*d;
	size_t	n;
	size_t	d_len;

	if (src == NULL || dst == NULL)
		return (0);
	n = size;
	s = (char*)src;
	d = dst;
	while (n && *d)
	{
		d++;
		n--;
	}
	if (n == 0)
		return (ft_strlen(src) + size);
	d_len = ft_strlen(dst);
	while (--n)
		*d++ = *s++;
	*d = 0;
	return (d_len + ft_strlen(src));
}
