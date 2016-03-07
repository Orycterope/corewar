/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:13:49 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 15:11:54 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	c;

	str = (char*)malloc(sizeof(char) * size);
	if (str == NULL)
		return (NULL);
	c = 0;
	while (c < size)
		str[c++] = '\0';
	return (str);
}
