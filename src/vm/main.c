/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:08:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/08 20:02:12 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "arena.h"
#include "parameters.h"
#include "execution.h"
#include "display.h"

static void		check_dump(char **argv, t_arena *arena)
{
	int		i;

	i = 0;
	if (argv[2] == NULL)
	{
		ft_putendl("Error: Positive number expected after -dump.");
		exit(1);
	}
	while (argv[2][i])
	{
		if (!(argv[2][i] >= '0' && argv[2][i] <= '9'))
		{
			ft_putendl("Error: Positive number expected after -dump.");
			exit(1);
		}
		i++;
	}
	arena->dump_cycle = ft_atoi(argv[2]);
}

static void		check_param(int *argc, char ***argv, t_arena *arena)
{
	if (*argc == 1)
	{
		ft_printf("Error: No parameters. Expected entry :\n\n\
./corewar [-dump N] [[-n N] champion1.cor] ...\n\
-dump N : Dumps memory after N cycles then exits\n\
-n N : The following champion will be the number N.\n");
		exit(1);
	}
	if (ft_strcmp("-v", (*argv)[1]) == 0)
	{
		arena->display = (t_display *)1;
		*argv += 1;
		*argc -= 1;
	}
	else if (ft_strcmp("-dump", (*argv)[1]) == 0)
	{
		check_dump(*argv, arena);
		*argv += 2;
		*argc -= 2;
	}
	*argv += 1;
	*argc -= 1;
}

static void		print_winner(t_arena *arena)
{
	t_player	*p;
	t_player	*best;

	best = p = arena->players;
	while (p != NULL)
	{
		if (p->last_live >= best->last_live)
			best = p;
		p = p->next;
	}
	printf("The fight has ended with the last survivor dying at cycle %d.\n\
The winner is %s ! Its last words : \"%s\".\n",
best->last_live, best->name, best->comment);
}

int				main(int argc, char **argv)
{
	t_arena	*arena;

	arena = create_arena();
	check_param(&argc, &argv, arena);
	save_players(argc, argv, arena);
	load_players(arena);
	if (arena->display != NULL)
		init_display(arena);
	else
		display_champions(arena);
	start_fight(arena);
	if (arena->cycle != arena->dump_cycle)
	{
		if (arena->display != NULL && !arena->display->quitting)
			print_winner_display(arena);
		else
			print_winner(arena);
	}
	destroy_arena(arena);
	return (0);
}
