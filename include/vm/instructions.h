/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:19:58 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/13 22:23:51 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	INSTRUCTIONS_H
# define INSTRUCTIONS_H

int				alive(t_process *process);
int				load(t_process *process);
int				store(t_process *process);
int				addition(t_process *process);
int				soustraction(t_process *process);
int				ft_and(t_process *process);
int				ft_or(t_process *process);
int				ft_xor(t_process *process);
int				zjump(t_process *process);
int				load_index(t_process *process);
int				store_index(t_process *process);
int				fork(t_process *process);
int				long_load(t_process *process);
int				long_load_index(t_process *process);
int				long_fork(t_process *process);
int				aff(t_process *process);

#endif
