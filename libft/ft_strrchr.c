/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 19:24:20 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:44:48 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*occ;

	while (*s)
		if (*s++ == (unsigned char)c)
			occ = ((char *)s - 1);
	return ((unsigned char)c == '\0' ? (char*)s : occ);
}
