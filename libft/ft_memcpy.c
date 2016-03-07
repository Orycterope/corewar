/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 13:37:33 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:19:16 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst2;

	if (dst == NULL || src == NULL)
		return (NULL);
	dst2 = dst;
	while (n--)
		*dst2++ = *(unsigned char *)src++;
	return (dst);
}
