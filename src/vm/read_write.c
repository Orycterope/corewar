/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_endianness.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 16:11:26 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/07 15:02:57 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "arena.h"
#include "display.h"
#define PA p->arena

static void	save_for_display(t_process *p, int index)
{
	t_d_update	*u;

	if (index < 0 || index >= MEM_SIZE)
		return ;
	u = get_update_struct_of(index, p->arena);
	if (u == NULL)
		return ;
	u->owner = p->player;
	u->w_turns = D_WRITE_TURNS;
	p->arena->display->owner_tab[index] = (char)p->player;
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
			save_for_display(p, (int)(dest - a->memory));
		*dest-- = (n & 0xFF);
		n >>= 8;
		i++;
	}
	return (i);
}

long long	rm(char *src, size_t length, t_process *p)
{
	long long		n;
	long long		power;

	n = 0;
	power = 1;
	while (length > 0)
	{
		if (src >= p->arena->memory + MEM_SIZE)
			src -= MEM_SIZE;
		n += ((long long)((unsigned char *)src)[length - 1]) * power;
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
