/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alias.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 21:30:20 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 14:46:43 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "alias.h"

t_conversion	*resolve_alias(t_conversion *conv)
{
	char	*newflags;

	if (conv == NULL)
		return (NULL);
	if (ft_strchr("DOUCS", conv->conversion) != NULL)
	{
		free(conv->modifier);
		conv->modifier = ft_strdup("l");
		conv->conversion = ft_tolower(conv->conversion);
	}
	else if (conv->conversion == 'p')
	{
		newflags = ft_strjoin(conv->flags, "#");
		free(conv->flags);
		conv->flags = newflags;
		free(conv->modifier);
		conv->modifier = ft_strdup("l");
	}
	return (conv);
}
