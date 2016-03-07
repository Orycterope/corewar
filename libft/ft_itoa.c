/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 13:18:51 by tvermeil          #+#    #+#             */
/*   Updated: 2015/11/27 16:02:05 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_size(int n)
{
	int c;

	c = 1;
	if (n < 0)
	{
		n = -n;
		c++;
	}
	while ((n /= 10) > 0)
		c++;
	return (c + 1);
}

char		*ft_itoa(int n)
{
	char	*str;
	int		is_neg;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = get_size(n);
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	is_neg = (n < 0) ? 1 : 0;
	n = (n < 0) ? -n : n;
	str[--len] = 0;
	while (len-- > 0)
	{
		str[len] = (n % 10) + '0';
		n /= 10;
	}
	if (is_neg)
		*str = '-';
	return (str);
}
