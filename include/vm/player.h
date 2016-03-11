/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:37:26 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/11 14:17:53 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H
# include "libft.h"
# include "op.h"
# define BUFF_SIZE 1

typedef struct			s_arena t_arena;

typedef struct			s_player
{
	int					id;
	char				*name;
	char				*comment;
	int					champ_size;
	char				*begin;
	int					last_live;
	struct s_player		*next;
}						t_player;

void					get_input(int fd, t_player *player);
void					save_players(int ac, char **av, t_arena *arena)
void					free_players(t_arena *arena);

#endif
