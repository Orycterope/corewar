/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 14:45:47 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 22:32:55 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wordnbr(char const *s, char c)
{
	int	words;

	words = 1;
	while (*++s)
		if (*s == c && *(s - 1) != c)
			words++;
	return (words);
}

static int	ft_wordlen(char const *s, char c)
{
	int len;

	len = 1;
	while (*s == c && *s != '\0')
		s++;
	while (*s != c && *s++ != '\0')
		len++;
	return (len);
}

static char	*ft_cpyword(char const *s, char c)
{
	char	*wordstart;
	char	*parser;

	while (*s == c)
		s++;
	if (!(wordstart = (char *)malloc(sizeof(char) * ft_wordlen(s, c))))
		return (NULL);
	parser = wordstart;
	while (*s != c && *s != 0)
		*parser++ = *s++;
	*parser = '\0';
	return (wordstart);
}

static char	*ft_nextword(char const *s, char c)
{
	while (*s == c && *s != 0)
		s++;
	while (*s != c && *s != 0)
		s++;
	return ((char *)s);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	*word;
	int		i;

	if (s == NULL)
		return (NULL);
	if (!(tab = (char **)malloc(sizeof(char*) * ft_wordnbr(s, c))))
		return (NULL);
	i = 0;
	while (*s && ft_wordlen(s, c) > 1)
	{
		word = ft_cpyword(s, c);
		if (word == NULL)
			return (NULL);
		tab[i++] = word;
		s = ft_nextword(s, c);
	}
	tab[i] = 0;
	return (tab);
}
