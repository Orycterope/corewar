/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 18:22:28 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/24 18:28:36 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_power(int value, int power)
{
	int result;

	result = value;
	if (power == 0)
		return (1);
	while (power > 1)
	{
		result *= value;
		power--;
	}
	return (result);
}
