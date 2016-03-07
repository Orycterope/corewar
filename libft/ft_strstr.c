/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:36:55 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:20:43 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	size_t	parser;

	if (*s2 == '\0')
		return ((char *)s1);
	while (*s1)
	{
		parser = 0;
		while (s1[parser] == s2[parser] || s2[parser] == '\0')
			if (s2[parser++] == '\0')
				return ((char *)s1);
		s1++;
	}
	return (NULL);
}
