/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rporcon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 10:00:30 by rporcon           #+#    #+#             */
/*   Updated: 2016/03/11 11:48:52 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include "../../include/libft/libft.h"
# include "../../include/libft/get_next_line.h"
# include "../../include/asm/op.h"
// # include "../../include/libft/ft_printf.h"


typedef struct			s_label
{
	struct s_label		*next;
	struct s_instruc	*insts;
	char				*name;
}						t_label;

typedef struct			s_instruc
{
	struct s_instruc	*next;
	char				*name;
	int					opcode;
}						t_instruc;

typedef struct			s_data
{

}						t_data;

void					init_data(t_data *data);
void					free_data(t_data *data);
void					set_filename(t_data *data, char *name);
int						is_in_str(char c, char *str);
char					*rem_char(char *str, char *rem);
void					read_name_comment(t_data *data, char *str);
void					parser(int fd, t_data *data);
// error
void					error_at(char *err, int line, int column);
void					error(char *err);
// lst fct
t_label					*lbl_new_elem(char *name);
t_label					addend_lbl_lst(t_label **lst, t_label *new_elem);
t_label					print_lbl_lst(t_label **lst);
t_instruc				*inst_new_elem(char *name);
t_instruc				addend_inst_lst(t_instruc **lst, t_label *new_elem);
t_instruc				print_inst_lst(t_instruc **lst);
