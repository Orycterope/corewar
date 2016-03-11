/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 19:03:23 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/11 18:17:07 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARENA_H
# define ARENA_H
# include "process.h"
# include "player.h"

typedef struct	s_process t_process;
typedef struct	s_player t_player;

typedef struct	s_arena
{
	char		*memory;
	t_player	*players;
	int			cycle;
	int			cycle_to_die;
	int			last_check_cycle;
	int			checks_without_decrement;
	int			dump_cycle;
	t_process	*processes;
}				t_arena;

t_arena			*create_arena(void);
void			destroy_arena(t_arena *arena);
void			display_champions(t_arena *arena);
void			dump_memory(t_arena *arena);

#endif
