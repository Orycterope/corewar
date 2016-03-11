/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/07 15:07:56 by tvermeil          #+#    #+#             */
/*   Updated: 2016/01/07 15:13:14 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTF_H
# define UTF_H
# include "libft.h"
# include <wchar.h>

long long	convert_utf(wint_t arg);
char		*convert_utf_string(wint_t *list);

#endif
