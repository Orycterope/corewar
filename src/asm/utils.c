/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/21 17:33:01 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/22 14:16:05 by rporcon          ###   ########.fr       */
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
