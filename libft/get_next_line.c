/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/12 16:31:24 by jriallan          #+#    #+#             */
/*   Updated: 2016/02/21 22:07:10 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	size_line(char *text, int limit)
{
	char *pos;

	if (text != NULL)
	{
		pos = text;
		while (*pos != '\n' && pos - text < limit)
			pos++;
		return (pos - text);
	}
	return (0);
}

static int	found_fd(t_file **file, int fd)
{
	if (*file != NULL)
	{
		while ((*file)->next != NULL && (*file)->fd != fd)
			*file = (*file)->next;
		if ((*file)->fd == fd)
			return (1);
	}
	return (0);
}

static int	init(t_file **file_sav, t_file **file, int fd)
{
	t_file			*fil;

	*file = *file_sav;
	if (fd < 0 || *file == NULL || (*file != NULL && found_fd(file, fd) == 0))
	{
		if (fd < 0 || (fil = ft_memalloc(sizeof(t_file))) == NULL)
			return (-1);
		if ((fil->text = ft_memalloc(sizeof(char) * BUFF_SIZE)) == NULL)
			return (-1);
		fil->size_text = 0;
		fil->fd = fd;
		fil->next = NULL;
		if (*file != NULL)
			(*file)->next = fil;
		*file = (*file == NULL ? fil : (*file)->next);
	}
	else if (found_fd(file, fd) == 1 && (*file)->text == NULL)
	{
		if (((*file)->text = ft_memalloc(sizeof(char) * BUFF_SIZE)) == NULL)
			return (-1);
		(*file)->size_text = 0;
	}
	return (1);
}

static int	reduce(t_file **file, int size)
{
	t_file			*fil;
	char			*add;

	fil = *file;
	if (size_line(fil->text, fil->size_text) == 0 && fil->size_text == 0)
		fil->size_text = read(fil->fd, fil->text, BUFF_SIZE);
	if (fil->size_text <= 0 && fil->text != NULL)
		ft_strdel(&(fil->text));
	if (fil->size_text <= 0)
		fil->text = NULL;
	if (fil->size_text <= 0)
		return (fil->size_text < 0 ? -1 : 0);
	while (size_line(fil->text, fil->size_text) >= fil->size_text && size > 0)
	{
		size = BUFF_SIZE + fil->size_text;
		if ((add = (char *)malloc(sizeof(char) * size)) == NULL)
			return (-1);
		ft_strncpy(add, fil->text, fil->size_text);
		ft_strdel(&(fil->text));
		fil->text = add;
		add += fil->size_text;
		size = read(fil->fd, add, BUFF_SIZE);
		fil->size_text += size;
	}
	return (1);
}

int			get_next_line(int const fd, char **line)
{
	static t_file	*file = NULL;
	t_file			*fil;
	int				s;
	char			*new;

	if (init(&file, &fil, fd) < 0)
		return (-1);
	file = (file == NULL ? fil : file);
	if ((s = reduce(&fil, 1)) != 1)
		return (s);
	s = size_line(fil->text, fil->size_text);
	if ((new = (char *)malloc(sizeof(char) * (s + 1))) == NULL)
		return (-1);
	ft_bzero(new, s + 1);
	ft_strncpy(new, fil->text, s);
	*line = new;
	s = fil->size_text - s - 1;
	if ((new = (char*)malloc(sizeof(char) * (s > 0 ? s : BUFF_SIZE))) == NULL)
		return (-1);
	if (s > 0)
		ft_strncpy(new, &fil->text[fil->size_text - s], s);
	ft_strdel(&(fil->text));
	fil->size_text = s;
	fil->text = new;
	return (1);
}
