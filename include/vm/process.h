/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 18:42:10 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/11 17:29:34 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "arena.h"

typedef struct			s_arena t_arena;

typedef struct			s_process
{
	int					player; //
	char				**registers;
	char				*pc;
	char				carry;
	int					cycles_to_wait;
	int					lives;
	t_arena				*arena;
	struct s_process	*next;
}						t_process;

void					fork_process(t_process *process, char *pc);
void					kill_process(t_process *process);
void					execute_process(t_process *process);

#endif
