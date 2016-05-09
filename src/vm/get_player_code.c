/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_code.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:12:23 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/09 18:19:24 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arena.h"
#include "player.h"
#include <fcntl.h>

static char	*read_prog(int fd, char *memory, unsigned int *prog_size_read)
{
	int		i;
	int		ret;
	char	buf[BUFF_SIZE];

	i = 0;
	while ((ret = read(fd, buf, BUFF_SIZE) != 0))
	{
		if (ret == -1)
		{
			ft_putendl_fd("Error: The reading has failed.", 2);
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

	player->champ_size = 0;
	if ((fd = open(player->file_name, O_RDONLY)) < 0)
	{
		ft_printf_fd(2, "Error: Open file %s failed.\n", player->file_name);
		exit(1);
	}
	get_input(fd, player, &prog_size);
	player->begin = read_prog(fd, player->begin, &player->champ_size);
	if (prog_size != player->champ_size)
	{
		ft_printf_fd(2, "Error: File %s has a code size that differs \
from what its header says.\n", player->file_name);
		exit(1);
	}
	if ((close(fd)) == -1)
	{
		ft_printf_fd(2, "Error: Close file %s failed.\n", player->file_name);
		exit(1);
	}
}
