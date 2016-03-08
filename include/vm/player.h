/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:37:26 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/08 19:42:19 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "libft.h"

typedef struct	s_arena t_arena;

typedef struct	s_player
{
	int			id;
	char		*name;
	char		*comment;
	char		*weight;
	char		*begin;
	int			lives;
	s_player	*next;
}				t_player;

int				add_player_to_arena(t_arena *arena, char *begin);
int				check_player_is_dead(int id, t_arena *arena);
void			remove_player(int id, t_arena *arena);

#endif
