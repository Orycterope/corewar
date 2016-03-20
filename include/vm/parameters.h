/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 20:35:06 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/20 17:39:51 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H
# define PR process->registers
# define PV param.value
# define PA process->arena

typedef struct	s_parameters
{
	char		type[4];
	long long	value[4];
	int			jump;
	char		o;
}				t_parameters;

void			decode_ocp(t_process *process, t_parameters *param, int i);
void			params_value(t_process *process, t_parameters *param, int j);
int				check_registers(t_parameters *param, t_process *process, int j);
int				execute_instruction(t_process *process);
int				check_param_error(t_parameters params, int i);
void			change_carry(t_process *process, unsigned int value);

#endif
