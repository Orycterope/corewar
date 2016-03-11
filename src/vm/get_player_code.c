/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:12:23 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/11 21:31:27 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "player.h"
#include <fcntl.h>

static char	*read_prog(int fd, char *memory, unsigned int *prog_size_read)
{
	int			i;
	int		ret;
	char	buf[BUFF_SIZE];

	i = 0;
	while ((ret = read(fd, buf, BUFF_SIZE) != 0))
	{
		if (ret == -1)
		{
			ft_putendl("Error: The reading has failed.");
			exit(1);
		}
		memory[i] = buf[0];
		*prog_size_read += 1;
		i++;
	}
	return (memory);
}

void		get_player_code(t_player *player)
{
	int				fd;
	unsigned int	prog_size;
	unsigned int	prog_size_read;

	prog_size_read = 0;
	if ((fd = open(player->file_name, O_RDONLY)) < 0)
	{
		ft_putendl("Error: Open failed.");
		exit(1);
	}
	get_input(fd, player, &prog_size);
	player->begin = read_prog(fd, player->begin, &prog_size_read);
	if (prog_size != prog_size_read)
	{
		ft_printf("Error: File %s has a code size that differs \
				from what its header says\n", player->file_name);
		exit(1);
	}
}
