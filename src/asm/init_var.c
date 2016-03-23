/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:00:37 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/23 10:43:36 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_check_add_instruc(char ***inst_line, char **trim, int *ret)
{
	*inst_line = NULL;
	trim = NULL;
	*ret = 0;
}

void	init_check_add_lbl(t_label **new_elem, char ***sp_lbl_name,
		char **colon_chr)
{
	*new_elem = NULL;
	*sp_lbl_name = NULL;
	*colon_chr = NULL;
}
