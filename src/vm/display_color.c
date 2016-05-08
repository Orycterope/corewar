/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 15:37:53 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 15:39:49 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "display.h"

void		init_pairs(int players)
{
	int		o;
	int		oi;

	o = 0;
	while (++o <= players)
	{
		oi = -1;
		while (++oi < D_WRITE_TURNS + 1)
		{
			init_pair(10 * o + oi + MAX_PLAYERS + 1,
						100 + o * 10 + D_WRITE_TURNS - oi,
						0);
		}
	}
}

void		init_colors(t_player *p)
{
	float		i;
	short		r;
	short		g;
	short		b;
	int			c;

	c = 0;
	while (p != NULL)
	{
		color_content(p->id, &r, &g, &b);
		i = 11;
		while (--i > 0)
			init_color(
					100 + p->id * 10 + 9 - i,
					r + (((r + g + b) / 3 - r) + 400) * (i) / 25,
					g + (((r + g + b) / 3 - g) + 800) * (i) / 25,
					b + (((r + g + b) / 3 - b) + 700) * (i) / 25);
		init_pair(p->id, p->id, COLOR_BLACK);
		c++;
		p = p->next;
	}
	init_pairs(c);
}
