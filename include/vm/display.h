/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:08:20 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/30 23:16:15 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

typedef struct	s_display
{
	char		*memory;
	int			running;
	int			cps;
}				t_display;

void		init_display();
void		destroy_display(t_arena *arena);
void		print_mem(t_arena *arena);

#endif
