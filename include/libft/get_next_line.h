/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tvermeil <tvermeil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/07 17:14:21 by tvermeil          #+#    #+#             */
/*   Updated: 2015/12/12 22:06:29 by tvermeil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <unistd.h>
# define BUFF_SIZE 128

typedef struct			s_pendant
{
	int					fd;
	char				*str;
	struct s_pendant	*next;
}						t_pendant;

int						get_next_line(int const fd, char **line);

#endif
