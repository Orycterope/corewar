/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:18:51 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 14:53:11 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "itoa.h"

static int	get_size(long long n)
{
	int		c;

	c = 1;
	if (n < 0)
		c++;
	while ((n /= 10) != 0)
		c++;
	return (c + 1);
}

char		*itoa(long long n)
{
	char	*str;
	int		is_neg;
	int		len;

	len = get_size(n);
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	is_neg = (n < 0) ? 1 : 0;
	str[--len] = 0;
	while (len-- > 0)
	{
		str[len] = (n % 10) * (n < 0 ? -1 : 1) + '0';
		n /= 10;
	}
	if (is_neg)
		*str = '-';
	return (str);
}
