/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:08:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/09 19:01:25 by adubedat         ###   ########.fr       */
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
		ft_putendl_fd("Error: Positive number expected after -dump.", 2);
		exit(1);
	}
	while (argv[2][i])
	{
		if (!(argv[2][i] >= '0' && argv[2][i] <= '9'))
		{
			ft_putendl_fd("Error: Positive number expected after -dump.", 2);
			exit(1);
		}
		i++;
	}
	arena->dump_cycle = ft_atoi(argv[2]);
}

static void		check_param2(int *argc, char ***argv, t_arena *arena)
{
	if (ft_strcmp("-dump", (*argv)[1]) == 0)
	{
		check_dump(*argv, arena);
		*argv += 2;
		*argc -= 2;
	}
	else if (ft_strcmp("-l", (*argv)[1]) == 0)
	{
		arena->print_lives = 1;
		*argv += 1;
		*argc -= 1;
	}
}

static void		check_param(int *argc, char ***argv, t_arena *arena)
{
	if (*argc == 1)
	{
		ft_putendl_fd("Error: No parameters. Expected entry :\n", 2);
		ft_putendl_fd("./corewar [-dump N] [[-n N] champion1.cor] ...", 2);
		ft_putendl_fd("-dump N : Dumps memory after N cycles then exits", 2);
		ft_putendl_fd("-n N : The following champion will be the number N", 2);
		ft_putendl_fd("-v : Display corewar arena", 2);
		ft_putendl_fd("-l : Print lives", 2);
		exit(1);
	}
	if (ft_strcmp("-v", (*argv)[1]) == 0)
	{
		check_display_and_n_flags(*argv);
		arena->display = (t_display *)1;
		*argv += 1;
		*argc -= 1;
	}
	else
		check_param2(argc, argv, arena);
	*argv += 1;
	*argc -= 1;
}

static void		print_winner(t_arena *arena)
{
	t_player	*p;
	t_player	*best;

	best = arena->players;
	p = arena->players;
	while (p != NULL)
	{
		if (p->last_live >= best->last_live)
			best = p;
		p = p->next;
	}
	ft_printf("The fight has ended with the last survivor dying at cycle %d.\n"
		"The winner is %s ! Its last words : \"%s\".\n",
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
