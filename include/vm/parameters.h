/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adubedat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 20:35:06 by adubedat          #+#    #+#             */
/*   Updated: 2016/03/15 23:27:17 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARAMETERS_H
# define PARAMETERS_H
# define PR process->registers
# define RBE ft_read_big_endian
# define PV param.value
# define PA process->arena
# define WBE ft_write_big_endian

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
int				check_param_error(t_process *process, t_parameters params, int i);

#endif
