/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:33:01 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/29 10:22:41 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

char	*no_comma(char *str)
{
	char	**comma_split;
	char	*ret;

	comma_split = ft_strsplit(str, ',');
	ret = ft_strdup(comma_split[0]);
	free_strsplit(comma_split);
	return (ret);
}

char	*ft_pass_space_tab(char *str)
{
	int	index;

	index = 0;
	while (str[index] != '\0' && (str[index] == ' ' || str[index] == '\t'))
		index++;
	return (str + index);
}
