/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianess.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/20 15:55:23 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/30 23:04:30 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENDIANESS_H
# define ENDIANESS_H

int			wm(long long n, void *dst, size_t l, t_process *p);
long long	rm(void *src, size_t length, t_process *p);

#endif
