/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:19:58 by adubedat          #+#    #+#             */
/*   Updated: 2016/05/08 21:41:10 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INSTRUCTIONS_H
# define INSTRUCTIONS_H
# define PR	process->registers
# define RBE	ft_read_big_endian
# define WBE	ft_write_big_endian

int				alive(t_process *process, int i);
int				load(t_process *process, int i);
int				store(t_process *process, int i);
int				addition(t_process *process, int i);
int				soustraction(t_process *process, int i);
int				ft_and(t_process *process, int i);
int				ft_or(t_process *process, int i);
int				ft_xor(t_process *process, int i);
int				zjump(t_process *process, int i);
int				load_index(t_process *process, int i);
int				store_index(t_process *process, int i);
int				ft_fork(t_process *process, int i);
int				long_load(t_process *process, int i);
int				long_load_index(t_process *process, int i);
int				long_fork(t_process *process, int i);
int				aff(t_process *process, int i);

#endif
