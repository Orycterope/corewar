/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 20:27:41 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:16:52 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	parser;

	if (*s2 == '\0')
		return ((char *)s1);
	while (n && *s1 != 0)
	{
		parser = 0;
		while ((s1[parser] == s2[parser] || s2[parser] == '\0') && parser <= n)
			if (s2[parser++] == '\0')
				return ((char *)s1);
		s1++;
		n--;
	}
	return (NULL);
}
