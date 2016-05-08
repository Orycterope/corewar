/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/13 22:22:14 by tvermeil          #+#    #+#             */
/*   Updated: 2016/03/15 20:43:15 by adubedat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERATION_H
# define OPERATION_H

typedef	struct	s_op
{
	char	*name;
	int		param_nbr;
	char	param_type[4];
	char	op_code;
	int		cycles;
	char	*comment;
	int		has_ocp;
	int		c2;
}				t_op;

#endif
