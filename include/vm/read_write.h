/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_write.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/08 21:41:30 by tvermeil          #+#    #+#             */
/*   Updated: 2016/05/08 21:41:59 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_WRITE_H
# define READ_WRITE_H

int			wm(long long n, void *dst, size_t l, t_process *p);
long long	rm(void *src, size_t length, t_process *p);

#endif
