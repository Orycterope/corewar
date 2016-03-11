/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 17:28:40 by tvermeil          #+#    #+#             */
/*   Updated: 2015/12/18 19:22:50 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "itoa_base.h"

static int	get_size(unsigned long long n, int base)
{
	int		c;

	c = 1;
	while ((n /= base) > 0)
		c++;
	return (c + 1);
}

char		*itoa_base(unsigned long long n, char *charset)
{
	char	*str;
	int		base;
	int		len;

	base = ft_strlen(charset);
	len = get_size(n, base);
	str = (char *)malloc(sizeof(char) * len);
	if (str == NULL)
		return (NULL);
	str[--len] = 0;
	while (len-- > 0)
	{
		str[len] = charset[n % base];
		n /= base;
	}
	return (str);
}
