/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_var.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/14 11:00:37 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/22 18:33:53 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	init_check_add_instruc(char ***inst_line, char **trim,
		t_instruc **new_elem)
{
	*inst_line = NULL;
	trim = NULL;
	*new_elem = NULL;
}

void	init_check_add_lbl(t_label **new_elem, char ***sp_lbl_name,
		char **colon_chr)
{
	*new_elem = NULL;
	*sp_lbl_name = NULL;
	*colon_chr = NULL;
}
