/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endianness.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:11:26 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/30 23:46:19 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "arena.h"
#include "display.h"
#define PA p->arena

static void	save_wr_for_display(t_process *p, char *display_c, int w_r)
{
	if ((*display_c >> 5) != p->player)
		*display_c = 0x00;
	*display_c = (*display_c & 0x1F) | (p->player << 5);
	*display_c |= (w_r << 3);
	*display_c = (*display_c & 0xF8) | 0x06;
}

int			wm(long long n, void *dst, size_t l, t_process *p)
{
	size_t	i;
	char	*dest;
	t_arena	*a;

	if (l == 0)
		return (0);
	dest = (char *)(dst + l - 1);
	a = p->arena;
	i = 0;
	while (i < l)
	{
		if (dest >= a->memory + MEM_SIZE)
			dest -= MEM_SIZE;
		else if (dest < a->memory)
			dest += MEM_SIZE;
		if (a->display != NULL)
			save_wr_for_display(p, dest - a->memory + a->display->memory, 1);
		*dest-- = (n & 0xFF);
		n >>= 8;
		i++;
	}
	return (i);
}

long long	rm(void *src, size_t length, t_process *p)
{
	long long		n;
	long long		power;
	//unsigned char	*ptr;
	char			*ptr;

	n = 0;
	power = 1;
	//ptr = (unsigned char *)src;
	ptr = src;
	while (length > 0)
	{
		if (ptr >= p->arena->memory + MEM_SIZE)
			ptr -= MEM_SIZE;
		if (PA->display != NULL)
			save_wr_for_display(p,
					&(ptr[length - 1]) - PA->memory + PA->display->memory, 2);
		n += ((long long)((unsigned char *)ptr)[length - 1]) * power; // if (ptr is signed char * no need to loop after for neg values) ?
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
