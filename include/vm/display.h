/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:08:20 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/30 18:11:27 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H

typedef struct	s_display
{
	char		*belonging;
	int			running;
	int			cps;
}				t_display;

void		init_display();
void		print_mem(t_arena *arena);

#endif
