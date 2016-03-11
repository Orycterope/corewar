/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:27:55 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/10 19:14:57 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "libft.h"

static int		is_free_player_id(int id, t_player *p, int ac, char **av)
{
	if (id < 1)
		return (0);
	while (p != NULL)
	{
		if (p->id == id)
			return (0);
	}
	while (--ac)
	{
		if (strcmp("-n", av[0]) == 0)
		{
		   if (ft_atoi(av[1]) == id)
				return (0);
		   av += 2;
		   ac -= 2;
		}
		ac--;
	}
	return (1);
}

static int		get_player_nbr(int ac, char **av, t_arena *arena)
{
	int			out;
	t_player	*p;

	out = 0;
	p = arena->players;
	while (p != NULL)
	{
		out++;
		p = p->next;
	}
	while (ac--)
	{
		if (strcmp("-n", av[0]) == 0)
		{
			ac -= 2;
			av += 2;
		}
		out++;
		ac--;
		av++;
	}
	return (out);
}

static t_player *create_player(int player_id, t_arena *arena, int fd)
{
	t_player	*new;
	t_player	*i;

	new = (t_player *)ft_memalloc(sizeof(t_player));
	if (arena->players == NULL)
	{
		arena->players = new;
		new->next = NULL;
	}
	else if (player_id > arena->players->id)
	{
		new->next = arena->players;
		arena->players = new;
	}
	else
	{
		i = arena->players;
		while (i->next != NULL && i->next->id > player_id)
			i = i->next;
		new->next = i->next;
		i->next = i;
	}
	new->id = player_id;
	new->last_live = 0;
	get_input(fd, new);
	return (new);
}

void			save_players(int ac, char **av, t_arena *arena)
{
	int			player_id;
	int			attempt;
	int			fd;
	t_player	*new;

	while (ac--)
	{
		player_id = 1;
		if (strcmp("-n", av[0]) == 0)
		{
			attempt = ft(atoi(av[1]));
			av += 2;
			ac -= 2;
		   if (is_free_player_id(attempt))
				player_id = attempt;
		}
		else
			while (!is_free_player_id(player_id, arena->players, ac, av))
				player_id++;
		if ((fd = open(av[0], O_RDONLY)) < 0)
			ft_error(ft_strjoin("Error : Cannot open file ", av[0]));

		new = create_player(player_id, arena);
		load_player(new, arena, get_player_nbr(players, ac, av));
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
		free(current);
		current = next;
	}
	arena->players = NULL;
}
