/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endianness.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:11:26 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/27 16:25:02 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "arena.h"

int			wm(long long n, void *dst, size_t l, t_arena *a)
{
	size_t	i;
	char	*dest;

	if (l == 0)
		return (0);
	dest = (char *)(dst + l - 1);
	i = 0;
	while (i < l)
	{
		if (dest >= a->memory + MEM_SIZE)
			dest -= MEM_SIZE;
		else if (dest < a->memory)
			dest += MEM_SIZE;
		*dest-- = (n & 0xFF);
		n >>= 8;
		i++;
	}
	return (i);
}

long long	rm(void *src, size_t length, t_arena *arena)
{
	long long		n;
	long long		power;
	unsigned char	*ptr;

	n = 0;
	power = 1;
	ptr = (unsigned char *)src;
	while (length > 0)
	{
		if (ptr >= (unsigned char *)arena->memory + MEM_SIZE)
			ptr -= MEM_SIZE;
		n += ((long long)ptr[length - 1]) * power;
		power <<= 8;
		length--;
	}
	if ((n & (power >> 1)) != 0)
		while (power != 0x0)
		{
			n |= power;
			power <<= 1;
		}
	return (n);
}
