/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:37:26 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/11 14:05:30 by tvermeil         ###   ########.fr       */
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
	char		*champ_size;
	char		*file_name;
	char		*begin;
	int			last_live;
	s_player	*next;
}				t_player;

int				check_player_is_dead(int id, t_arena *arena);
void			remove_player(int id, t_arena *arena);
void			save_players(int ac, char **av, t_arena *arena)
void			eliminate_player(t_player *player, t_arena *arena)
void			free_players(t_arena *arena);

#endif
