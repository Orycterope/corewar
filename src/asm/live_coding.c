/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   live_coding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:04:55 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 17:05:01 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	live_coding_mode(t_data *data, char *filename)
{
	char	*tmp;

	ft_printf("\t\t\033[32;1;4mLive Coding Mode\033[0m\n");
	while (filename == NULL || ft_strcmp(filename, "") == 0)
	{
		ft_printf("\033[36;1mEnter filename :\033[0m\n");
		get_next_line(0, &filename);
	}
	tmp = ft_strjoin(filename, ".s");
	free(filename);
	set_filename(data, tmp);
	free(tmp);
	ft_printf("\033[36;1mWrite your file here (type \033[34;1msave%s",
							"\033[36;1m when you have finish) :\033[0m\n");
	data->fd = 0;
}
