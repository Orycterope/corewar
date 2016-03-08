/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 18:42:10 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/08 19:04:41 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "vm.h"

typedef struct	s_arena t_arena;

typedef struct	s_process
{
	int			pid;
	int			player;
	char		**registers;
	char		*pc;
	char		carry;
	int			cycles_to_wait;
	int			lives;
	t_arena		*arena;
	s_process	*next;
	s_process	*previous;
}				t_process;

void	fork_process(t_process *process, int *pc);
void	kill_process(t_process *process);

#endif
