/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 20:35:06 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/13 22:24:33 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H

typedef struct	s_parameters
{
	char		type[3];
	long long	value[3];
	int			jump;
}				t_parameters;

void			decode_ocp(t_process *process, t_parameters *param);
void			params_value(t_process *process, t_parameters *param);
int				check_registers(t_parameters param, t_process *process);
int				execute_instruction(t_process *process);

#endif
