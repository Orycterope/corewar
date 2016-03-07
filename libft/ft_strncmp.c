/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 20:49:25 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:24:34 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (s1 == NULL || s2 == NULL || n == 0)
		return (0);
	while (n--)
		if (*(unsigned char *)s1++ != *(unsigned char *)s2++ || *s2 == 0)
			return (*(unsigned char *)--s1 - *(unsigned char *)--s2);
	return (0);
}
