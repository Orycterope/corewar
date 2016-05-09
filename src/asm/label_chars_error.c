/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_chars_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 13:53:06 by rporcon           #+#    #+#             */
/*   Updated: 2016/05/09 13:53:18 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	essential_char_in_label_chars(void)
{
	if (is_in_str(COMMENT_CHAR, LABEL_CHARS) > 0 || is_in_str(LABEL_CHAR,
		LABEL_CHARS) > 0 || is_in_str(DIRECT_CHAR, LABEL_CHARS) > 0 ||
		is_in_str(SEPARATOR_CHAR, LABEL_CHARS) > 0)
		error("Error, Essential CHAR in LABEL_CHARS");
}
