/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 17:48:14 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/09 17:37:59 by tvermeil         ###   ########.fr       */
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

void	check_display_and_n_flags(char **argv)
{
	while (*++argv)
	{
		if (ft_strcmp("-n", *argv) == 0)
		{
			ft_putendl("Flag -n cannot be used with flag -v");
			exit(0);
		}
	}
}
