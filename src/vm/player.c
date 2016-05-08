/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:27:55 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 21:31:18 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "libft.h"

static int		is_free_player_id(int id, t_player *p, int ac, char **av)
{
	if (id < 1)
		return (0);
	ac--;
	av++;
	while (p != NULL)
	{
		if (p->id == id)
			return (0);
		p = p->next;
	}
	while (ac-- > 0)
	{
		if (ft_strcmp("-n", av[0]) == 0)
		{
			if (ft_atoi(av[1]) == id)
				return (0);
			av += 2;
			ac -= 2;
		}
		av++;
	}
	return (1);
}

static void		create_player(int player_id, t_arena *arena, char *file_name)
{
	t_player	*new;
	t_player	*i;

	new = (t_player *)ft_memalloc(sizeof(t_player));
	if (arena->players == NULL)
	{
		arena->players = new;
		new->next = NULL;
	}
	else if (player_id < arena->players->id)
	{
		new->next = arena->players;
		arena->players = new;
	}
	else
	{
		i = arena->players;
		while (i->next != NULL && i->next->id < player_id)
			i = i->next;
		new->next = i->next;
		i->next = new;
	}
	new->id = player_id;
	new->last_live = 0;
	new->file_name = file_name;
}

void			save_players(int ac, char **av, t_arena *arena)
{
	int			player_id;
	int			attempt;

	while (ac-- > 0)
	{
		player_id = 1;
		if (ft_strcmp("-n", av[0]) == 0)
		{
			check_player(av[1]);
			attempt = ft_atoi(av[1]);
			av += 2;
			ac -= 2;
			if (is_free_player_id(attempt, arena->players, ac, av))
				player_id = attempt;
		}
		else
			while (!is_free_player_id(player_id, arena->players, ac, av))
				player_id++;
		create_player(player_id, arena, av[0]);
		av++;
	}
}

void			load_players(t_arena *arena)
{
	t_player	*i;
	int			n;
	int			total;

	total = 0;
	i = arena->players;
	while (i != NULL)
	{
		total++;
		i = i->next;
	}
	if (total < 1 || total > MAX_PLAYERS)
	{
		ft_putendl("Error : too many players");
		exit(1);
	}
	i = arena->players;
	n = 0;
	while (i != NULL)
	{
		i->begin = (arena->memory + n++ * MEM_SIZE / total);
		get_player_code(i);
		create_process(i->id, i->begin, arena, NULL);
		i = i->next;
	}
}

void			free_players(t_arena *arena)
{
	t_player	*next;
	t_player	*current;

	current = arena->players;
	while (current != NULL)
	{
		next = current->next;
		free(current->name);
		free(current->comment);
		free(current);
		current = next;
	}
	arena->players = NULL;
}
