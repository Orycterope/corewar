/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_string.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/05 12:47:48 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/05 12:56:44 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_STRING_H
# define GET_STRING_H
# include "ft_printf.h"

char	*get_processed_str(char *str, va_list args, int *length, char **end);

#endif
