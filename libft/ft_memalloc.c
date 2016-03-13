/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:14:02 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/13 16:25:03 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*ptr;
	size_t	c;

	ptr = (char*)malloc(size);
	if (ptr == NULL)
	{
		ft_putendl("Error : malloc failed. Exiting ...");
		exit(0);
	}
	c = 0;
	while (c < size)
		ptr[c++] = 0;
	return ((void*)ptr);
}
