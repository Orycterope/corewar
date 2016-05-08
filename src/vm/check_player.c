/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:48:14 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/08 17:51:43 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "player.h"

void	check_player(char *argv)
{
	int		i;

	i = 0;
	if (argv == NULL)
	{
		ft_putendl("Error: Positive number expected after -n.");
		exit(1);
	}
	while (argv[i])
	{
		if (!(argv[i] >= '0' && argv[i] <= '9'))
		{
			ft_putendl("Error: Positive number expected after -n.");
			exit(1);
		}
		i++;
	}
}
