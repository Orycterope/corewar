/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/10 16:37:45 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/11 18:39:29 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "op.h"
#include "libft.h"

static void			check_magic(int fd, char *buf, int ret, t_player *p)
{
	unsigned char	magic[4];
	int				i;

	i = 0;
	while (i < 4)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		{
			ft_putendl("Error : The reading has failed.");
			exit(1);
		}
		else
			magic[i] = buf[0];
		i++;
	}
	if (magic[0] != 0 || magic[1] != 234 || magic[2] != 131
			|| magic[3] != 243)
	{
		ft_printf("Error: File %s has an invalid header.", p->file_name);
		exit(1);
	}
}

static char			*get_name(int fd, char *buf, int ret, int i)
{
	char	*name;

	name = ft_memalloc(PROG_NAME_LENGTH + 1);
	name[PROG_NAME_LENGTH] = '\0';
	while (i < PROG_NAME_LENGTH + 4) //
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		{
			ft_putendl("Error : The reading has failed.");
			exit(1);
		}
		else
			name[i] = buf[0];
		i++;
	}
	return (name);
}

static unsigned int	get_prog_size(int fd, char *buf, int ret, int i)
{
	char	size[4];

	while (i < 4)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		{
			ft_putendl("Error : The reading has failed.");
			exit(1);
		}
		else
			size[i] = buf[0];
		i++;
	}
	return (size[0] * 16777216 + size[1] * 65536 + size[2] * 256 + size[3]);
}

static char			*get_comment(int fd, char *buf, int ret, int i)
{
	char	*comment;

	comment = ft_memalloc(COMMENT_LENGTH + 1);
	comment[COMMENT_LENGTH] = '\0';
	while (i < COMMENT_LENGTH + 4)
	{
		if ((ret = read(fd, buf, BUFF_SIZE)) == -1)
		{
			ft_putendl("Error : The reading has failed.");
			exit(1);
		}
		else
			comment[i] = buf[0];
		i++;
	}
	return (comment);
}

void				get_input(int fd, t_player *player, unsigned int *prog_size)
{
	int 			ret;
	char			buf[BUFF_SIZE];
	int				i;

	i = 0;
	check_magic(fd, buf, ret, player);
	player->name = get_name(fd, buf, ret, i);
	*prog_size = get_prog_size(fd, buf, ret, i);
	player->comment = get_comment(fd, buf, ret, i);
}
