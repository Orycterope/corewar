/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrapper.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/29 20:01:13 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 15:16:50 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wrapper.h"

static char	*get_left_part(char *str)
{
	char	*left_part;
	int		i;

	left_part = ft_strdup(str);
	i = 0;
	while (str[i] == '0' || str[i] == 'x' || str[i] == 'X'
			|| str[i] == '+' || str[i] == '-' || str[i] == ' ')
		i++;
	left_part[i] = '\0';
	return (left_part);
}

char		*zero_wrapper(char *str, size_t length)
{
	char	*out;
	char	*old;
	char	*left_part;

	left_part = get_left_part(str);
	out = ft_strdup(str + ft_strlen(left_part));
	free(str);
	while (ft_strlen(out) + ft_strlen(left_part) < length)
	{
		old = out;
		out = ft_strjoin("0", old);
		free(old);
	}
	old = out;
	out = ft_strjoin(left_part, old);
	free(old);
	free(left_part);
	return (out);
}

char		*space_wrapper(char *str, size_t length)
{
	char	*out;
	char	*old;

	out = str;
	while (ft_strlen(out) < length)
	{
		old = out;
		out = ft_strjoin(" ", old);
		free(old);
	}
	return (out);
}
