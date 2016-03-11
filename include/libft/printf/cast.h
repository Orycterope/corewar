/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 20:00:29 by tvermeil          #+#    #+#             */
/*   Updated: 2015/12/18 17:53:22 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_H
# define CAST_H
# include "ft_printf.h"
# include <stdint.h>

long long	get_arg(va_list args, t_conversion *conv);

#endif
