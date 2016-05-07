/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 18:08:20 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/07 18:21:42 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPLAY_H
# define DISPLAY_H
# define D_WRITE_TURNS 8
# include <ncurses.h>
# include "player.h"

typedef struct			s_arena t_arena;

typedef struct			s_d_update
{
	char				owner;
	char				w_turns;
	int					index;
	struct s_d_update	*next;
}						t_d_update;

typedef struct			s_display
{
	t_d_update			*updates;
	int					running;
	int					cps;
	int					quitting;
	WINDOW				*w_mem;
	WINDOW				*w_pcs;
	WINDOW				*w_bkp;
	WINDOW				*w_info;
	char				owner_tab[MEM_SIZE];
}						t_display;

void					init_display();
void					destroy_display(t_arena *arena);
void					init_info_display(t_arena *arena);
void					init_mem_display(t_arena *arena);
void					update_display(t_arena *arena);
void					highlight_rw(t_arena *arena);
int						highlight_pcs(t_arena *arena);
void					remove_update_struct(t_d_update *u, t_arena *arena);
t_d_update				*get_update_struct_of(int i, t_arena *arena);

void					check_keystroke(t_arena *arena);
void					update_infos(t_arena *arena);
void					regulate_speed(t_arena *arena);
void					init_colors(t_player *p);
void					print_winner_display(t_arena *a);

#endif
