/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_conversion_parts.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 16:48:29 by tvermeil          #+#    #+#             */
/*   Updated: 2015/12/16 23:52:46 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_CONVERSION_PARTS_H
# define GET_CONVERSION_PARTS_H
# include "ft_printf.h"
# include "libft.h"

char			*get_flags(char *str);
char			*get_width(char *str);
char			*get_precision(char *str);
char			*get_modifier(char *str);
char			get_conversion(char *str);

#endif
