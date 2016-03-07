/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 22:19:22 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:47:10 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_first(char const *s)
{
	while (*s == ' ' || *s == '\t' || *s == '\n')
		s++;
	return ((char *)s);
}

static char	*get_last(char const *s)
{
	const char	*start;

	start = s;
	while (*s)
		s++;
	while ((*s == ' ' || *s == '\t' || *s == '\n' || *s == '\0') && s != start)
		s--;
	return ((char *)s);
}

char		*ft_strtrim(char const *s)
{
	char	*start;
	char	*end;
	char	*trim;
	size_t	parser;

	if (s == NULL)
		return (NULL);
	start = get_first(s);
	end = get_last(s);
	if (end - start < 0)
		end = start;
	trim = (char *)malloc(sizeof(char) * (end - start + 1));
	if (trim == NULL)
		return (NULL);
	parser = -1;
	while (++parser <= (size_t)(end - start))
		trim[parser] = start[parser];
	trim[end - start + 1] = '\0';
	return (trim);
}
