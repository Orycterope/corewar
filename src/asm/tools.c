/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 14:59:06 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/29 10:28:31 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		is_in_str(char c, char *str)
{
	int		i;
	int		ret;

	ret = 0;
	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (c == str[i])
			ret++;
		i++;
	}
	return (ret);
}

int		str_is_in_str(char *search, char *str)
{
	int		i;

	i = 0;
	if (search == NULL)
		return (0);
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (is_in_str(str[i], search) == 0)
			return (1);
		i++;
	}
	return (0);
}

char	*rm_char(char *str, char *rem)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (is_in_str(str[i], rem) == 0)
			len++;
		i++;
	}
	if ((ret = (char *)malloc(sizeof(char) * ++len)) == NULL)
		error("Malloc error");
	ft_bzero(ret, len);
	i = 0;
	j = 0;
	while (str[j] != '\0')
	{
		if (is_in_str(str[j], rem) == 0)
			ret[i++] = str[j];
		j++;
	}
	return (ret);
}

void	free_strsplit(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] == 0)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

int		set_ocp(int ocp, int index, int val)
{
	if ((val == 0 || val == 1 || val == 2 || val == 3) &&
			(index == 0 || index == 1 || index == 2 || index == 3))
	{
		if (index == 0)
			val = val << 6;
		if (index == 1)
			val = val << 4;
		if (index == 2)
			val = val << 2;
		if (index == 0)
			ocp = ocp & 0x3f;
		if (index == 1)
			ocp = ocp & 0xcf;
		if (index == 2)
			ocp = ocp & 0xf3;
		if (index == 3)
			ocp = ocp & 0xfc;
		ocp = ocp | val;
	}
	return (ocp);
}
