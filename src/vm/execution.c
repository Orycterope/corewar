/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 20:30:34 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 21:24:33 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "player.h"
#include "process.h"
#include "op.h"
#include "operation.h"
#include "parameters.h"
#include "display.h"

extern t_op		g_op_tab[17];

void			get_wait_time(t_process **p)
{
	int	op_code;
	int	i;

	i = 0;
	op_code = (*p)->pc[0];
	(*p)->op_code = op_code;
	while (g_op_tab[i].name != NULL)
	{
		if (g_op_tab[i].op_code == op_code)
		{
			(*p)->cycles_to_wait = g_op_tab[i].cycles - 1;
			(*p)->op_code = op_code;
		}
		i++;
	}
}

static void		execute_processes(t_arena *arena)
{
	t_process	*p;

	p = arena->processes;
	while (p != NULL)
	{
		if (p->cycles_to_wait < 0)
			get_wait_time(&p);
		if (p->cycles_to_wait <= 0)
			p->pc = mem(p->pc + execute_instruction(p), 0, arena, p);
		p->cycles_to_wait--;
		p = p->next;
	}
}

static int		count_lives(t_arena *arena)
{
	t_process	*p;
	int			count;

	count = 0;
	p = arena->processes;
	while (p != NULL)
	{
		count += p->count_lives;
		p = p->next;
	}
	return (count);
}

static void		check_processes(t_arena *arena)
{
	t_process	*p;
	t_process	*next;

	p = arena->processes;
	while (p != NULL)
	{
		next = p->next;
		if (p->lives == 0)
			kill_process(p);
		else
		{
			p->count_lives = 0;
			p->lives = 0;
		}
		p = next;
	}
}

void			start_fight(t_arena *arena)
{
	int		lives;

	while (arena->processes != NULL && update_display(arena))
	{
		execute_processes(arena);
		if (arena->cycle >= arena->last_check_cycle + arena->cycle_to_die)
		{
			lives = count_lives(arena);
			check_processes(arena);
			arena->last_check_cycle = arena->cycle;
			arena->checks_without_decrement++;
			if (arena->checks_without_decrement >= MAX_CHECKS
					|| lives >= NBR_LIVE)
			{
				arena->cycle_to_die -= CYCLE_DELTA;
				arena->checks_without_decrement = 0;
			}
		}
		if (arena->cycle == arena->dump_cycle)
		{
			dump_memory(arena);
			break ;
		}
		arena->cycle++;
	}
}
