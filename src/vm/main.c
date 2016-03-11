/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 19:08:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/11 22:29:39 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"

static void	check_dump(char **argv, t_arena *arena)
{
	int		i;

	i = 0;
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

static void	check_param(int *argc, char ***argv, t_arena *arena)
{
	int	i;

	i = 0;
	if (*argc == 1)
	{
		ft_printf("Error: No parameters. Expected entry :\n\n\
./corewar [-dump N] [[-n N] champion1.cor] ...\n\
-dump N : Dumps memory after N cycles then exits\n\
-n N : The following champion will be the number N.\n");
		exit(1);
	}
	if (ft_strcmp("-dump", (*argv)[1]) == 0)
	{
		check_dump(*argv, arena);
		*argv += 2;
		*argc -= 2;
	}
	*argv += 1;
	*argc -= 1;
}

int				main(int argc, char **argv)
{
	t_arena	*arena;

	arena = create_arena();
	check_param(&argc, &argv, arena);
	arena = create_arena();
	save_players(argc, argv, arena);
	load_players(arena);
	display_champions(arena);
	dump_memory(arena);
	destroy_arena(arena);
	return (0);
}
