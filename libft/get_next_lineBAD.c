/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 14:49:57 by tvermeil          #+#    #+#             */
/*   Updated: 2015/12/12 22:02:48 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_pendant	*get_pendant_fd(int fd, t_pendant *pendant)
{
	t_pendant	*parser;

	parser = pendant;
	while (parser != NULL && parser->fd != fd)
		parser = parser->next;
	return (parser);
}

static int			add_pendant_fd(int fd, char *str, t_pendant **pendant)
{
	t_pendant	*new;
	t_pendant	*parser;

	new = (t_pendant*)malloc(sizeof(t_pendant));
	if (new == NULL)
		return (-1);
	new->fd = fd;
	new->str = str;
	new->next = NULL;
	if (*pendant == NULL)
	{
		*pendant = new;
		return (1);
	}
	parser = *pendant;
	while (parser->next != NULL)
		parser = parser->next;
	parser->next = new;
	return (1);
}

static void			remove_pendant_fd(int fd, t_pendant **pendant)
{
	t_pendant	*lst_parser;
	t_pendant	*previous;
	t_pendant	*next;

	if (*pendant == NULL)
		return ;
	lst_parser = *pendant;
	previous = NULL;
	while (lst_parser != NULL)
	{
		next = lst_parser->next;
		if (lst_parser->fd == fd)
		{
			free(lst_parser->str);
			free(lst_parser);
			if (previous != NULL)
				previous->next = next;
			else
				*pendant = next;
			return ;
		}
		else
			previous = lst_parser;
		lst_parser = next;
	}
}

static char			*split_str(char *str, int fd, t_pendant **pendant)
{
	int			i;
	t_pendant	*previous_pendant;

	previous_pendant = get_pendant_fd(fd, *pendant);
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			add_pendant_fd(fd, ft_strdup(&str[i + 1]), pendant);
			str[i] = '\0';
			break ;
		}
		i++;
	}
	if (previous_pendant != NULL)
		remove_pendant_fd(fd, pendant);
	return (str);
}

int					get_next_line(int const fd, char **line)
{
	char				buffer[BUFF_SIZE + 1];
	char				*join;
	char				*cpy;
	int					read_nbr;
	static t_pendant	*pendant;

	if (line == NULL)
		return (-1);
	join = NULL;
	if (get_pendant_fd(fd, pendant) != NULL)
		join = split_str(ft_strdup(get_pendant_fd(fd, pendant)->str),
				fd, &pendant);
	read_nbr = 1;
	while (get_pendant_fd(fd, pendant) == NULL
			&& (read_nbr = read(fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[read_nbr] = '\0';
		cpy = join;
		join = ft_strjoin(join, split_str(buffer, fd, &pendant));
		free(cpy);
	}
	*line = join;
	return ((read_nbr > 0) ? 1 : read_nbr);
}
