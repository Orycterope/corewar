/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianess.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:55:23 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/20 16:29:37 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDIANESS_H
# define ENDIANESS_H

int			wm(long long n, void *dst, size_t l, t_arena *a);
long long	rm(void *src, size_t length, t_arena *arena);

#endif
