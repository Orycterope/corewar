/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:53:04 by jriallan          #+#    #+#             */
/*   Updated: 2016/03/12 21:19:55 by jriallan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../include/libft/get_next_line.h"
# include "op.h"

typedef struct			s_instruc
{
	struct s_instruc	*next;
	char				*name;
	int					opcode;
	char				*param_1;
	char				*param_2;
	char				*param_3;
	char				ocp;
}						t_instruc;

typedef struct			s_label
{
	struct s_label		*next;
	t_instruc			*insts;
	char				*name;
}						t_label;

typedef struct			s_data
{
	char				*filename;
	char				*name;
	char				*comment;
	char				*cor;
	int					cor_len;
	t_label				*label;
	int					line;
	int					prog_size;
}						t_data;

void					write_header(t_data *data);
void					add_to_cor(t_data *data, char c);
void					add_str_to_cor(t_data *data, char *str, int len);
void					set_filename(t_data *data, char *name);
void					set_magic_to_cor(t_data	*data);
void					write_file(t_data *data);

void					init_data(t_data *data);
void					free_data(t_data *data);
int						is_in_str(char c, char *str);
char					*rm_char(char *str, char *rem);
void					free_strsplit(char **arr);
char					set_ocp(char ocp, char index, char val);
int						read_name_comment(t_data *data, char *str);
void					parser(int fd, t_data *data);

void					error_line(t_data *data, char *err);
void					error_limit(t_data *data, char *err,char *str, int limit);
void					error_at(char *err, int line, int column);
void					error_str(t_data *data, char *err, char *str);
void					error(char *err);

t_label					*lbl_new_elem(char *name);
void					addend_lbl_lst(t_label **lst, t_label *new_elem);
void					print_lbl_lst(t_label **lst);
t_instruc				*inst_new_elem(char *name);
void					addend_inst_lst(t_instruc **lst, t_instruc *new_elem);
void					print_inst_lst(t_instruc **lst);
int						check_add_lbl(char *buf, t_label *lbl_lst);
int						check_add_instruc(char *buf, t_label *lbl_lst);
int						check_opcode(char *str, t_instruc *inst);
void					check_opcode_suit(char *str, t_instruc *inst);
char					check_first_2param(char *str, t_instruc *inst);
char					check_second_2param(char *str, t_instruc *inst);
void					check_reg(char *str);
void					check_indirect(char *str);
void					check_direct(char *str);

#endif
