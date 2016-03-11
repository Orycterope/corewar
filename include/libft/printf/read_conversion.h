/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_conversion.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/15 14:17:17 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 15:05:20 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_CONVERSION_H
# define READ_CONVERSION_H

typedef struct	s_conversion
{
	char		*flags;
	char		*width;
	char		*precision;
	char		*modifier;
	char		conversion;
	int			length;
}				t_conversion;

t_conversion	*save_conversion_format(char *str);
void			free_conversion_format(t_conversion *conv);

#endif
