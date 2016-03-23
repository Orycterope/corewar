/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_cmt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 17:03:58 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/23 17:04:06 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int				check_quote_nm_cmt(t_data *data, char *str, char *cmd)
{
	int cont;

	cont = 0;
	if ((cont = is_in_str('"', str)) == 2 || cont == 1)
		return (cont);
	else
		error_str(data, "to many '\"' in ", cmd);
	return (-1);
}

void			init_nm_cmt(char **s, int len)
{
	if ((*s = (char *)malloc(sizeof(char) * (len + 1))) == NULL)
		error("Malloc error");
	ft_bzero(*s, len + 1);
}

int				nm_cmt(t_data *data, char **s, char **arr, int index)
{
	unsigned int	len;

	len = name_comment_len(index);
	if (arr[1] != 0 && (arr[2] == 0 ||
			(arr[2] + ft_strlen(arr[2])) == ft_pass_space_tab(arr[2])))
	{
		if (*s != NULL && index == 1)
			error_line(data, ERR_ALRD_SET_NAME);
		else if (*s != NULL)
			error_line(data, ERR_ALRD_SET_COMMENT);
		if (ft_strlen(arr[1]) > len && index == 1)
			error_limit(data, ERR_LENGTH_NAME, NULL, len);
		else if (ft_strlen(arr[1]) > len)
			error_limit(data, ERR_LENGTH_COM, NULL, len);
		init_nm_cmt(s, len);
		ft_strcpy(*s, arr[1]);
	}
	else if (arr[1] == 0)
		init_nm_cmt(s, len);
	else if (index == 1)
		error_line(data, ERR_LFT_QUOTE_NAME);
	else
		error_line(data, ERR_LFT_QUOTE_COMMENT);
	return (1);
}

unsigned int	parse_nm_cmt_init(int *ret, int index, char **cmd, char **str)
{
	*ret = 0;
	*cmd = name_comment(index);
	*str = ft_pass_space_tab(*str);
	return (name_comment_len(index));
}

int				parse_nm_cmt(t_data *data, char **s, char *str, int index)
{
	int				ret;
	int				cont;
	unsigned int	len;
	char			**arr;
	char			*cmd;

	len = parse_nm_cmt_init(&ret, index, &cmd, &str);
	if (ft_strncmp(str, cmd, ft_strlen(cmd)) == 0 &&
			*ft_pass_space_tab(str + ft_strlen(cmd)) == '"')
	{
		cont = check_quote_nm_cmt(data, str, cmd);
		arr = ft_strsplit(str, '"');
		ret = nm_cmt(data, s, arr, index);
		if (cont == 1 && arr[1] != 0)
			add_nm_cmt(data, s, len - ft_strlen(arr[1]), index);
		else if (cont == 1)
			add_nm_cmt(data, s, len, index);
		free_strsplit(arr);
	}
	else if (ft_strncmp(str, cmd, ft_strlen(cmd)) == 0 &&
			*ft_pass_space_tab(str + ft_strlen(cmd)) != '"')
		error_str(data, "character between '\"' and ", cmd);
	return (ret);
}
