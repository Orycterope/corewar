/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/08 18:42:10 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/09 19:14:48 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROCESS_H
# define PROCESS_H
# include "arena.h"
# include "op.h"
# define TP t_process

typedef struct s_arena	t_arena;

typedef struct			s_process
{
	int					player;
	char				registers[REG_NUMBER][REG_SIZE];
	char				*pc;
	char				carry;
	int					cycles_to_wait;
	int					lives;
	int					number;
	int					count_lives;
	int					op_code;
	t_arena				*arena;
	struct s_process	*next;
}						t_process;

void					fork_process(t_process *process, char *pc);
void					create_process(int p, char *pc, t_arena *a, TP *parent);
void					kill_process(t_process *process);
void					execute_process(t_process *process);
int						count_processes(t_arena *arena);

#endif
