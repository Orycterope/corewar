/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 20:54:45 by jriallan          #+#    #+#             */
/*   Updated: 2015/12/03 20:00:21 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_szwd(char const *s, char c)
{
	if (*s != '\0' && *s != c)
		return (ft_szwd(s + 1, c) + 1);
	return (0);
}

static int		ft_count_wrd(char *str, char c)
{
	int count;

	count = 0;
	while (*str != '\0')
	{
		if (*str != c && *str != '\0')
			count++;
		while (*str != c && *str != '\0')
			str++;
		while (*str == c)
			str++;
	}
	return (count);
}

char			**ft_strsplit(char const *s, char c)
{
	char	*str;
	char	**tab;
	int		i;
	int		word;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	word = ft_count_wrd(str, c);
	if ((tab = (char **)malloc(sizeof(char *) * (word + 1))) == NULL)
		return (NULL);
	i = 0;
	while (word--)
	{
		while (*str == c)
			str++;
		if (*str == '\0')
			break ;
		if ((tab[i++] = ft_strsub(str, 0, ft_szwd(str, c))) == NULL)
			return (NULL);
		while (*str != c && *str != '\0')
			str++;
	}
	tab[i] = 0;
	return (tab);
}
