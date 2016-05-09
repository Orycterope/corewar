/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:48:14 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/09 18:09:28 by adubedat         ###   ########.fr       */
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
		ft_putendl_fd("Error: Positive number expected after -n.", 2);
		exit(1);
	}
	while (argv[i])
	{
		if (!(argv[i] >= '0' && argv[i] <= '9'))
		{
			ft_putendl_fd("Error: Positive number expected after -n.", 2);
			exit(1);
		}
		i++;
	}
}

void	check_display_and_n_flags(char **argv)
{
	while (*++argv)
	{
		if (ft_strcmp("-n", *argv) == 0)
		{
			ft_putendl_fd("Flag -n cannot be used with flag -v", 2);
			exit(0);
		}
	}
}
