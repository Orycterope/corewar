/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jriallan <jriallan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/11 15:53:04 by jriallan          #+#    #+#             */
/*   Updated: 2016/05/09 13:57:15 by rporcon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include "../../include/libft/get_next_line.h"
# include "op.h"
# include "error.h"

typedef struct			s_instruc
{
	struct s_instruc	*next;
	char				*name;
	int					opcode;
	char				*param_1;
	char				*param_2;
	char				*param_3;
	char				*trim;
	int					ocp;
}						t_instruc;

typedef struct			s_label
{
	struct s_label		*next;
	t_instruc			*insts;
	char				*name;
}						t_label;

typedef struct			s_data
{
	int					verbose;
	int					binary;
	int					fd;
	char				*filename;
	char				*name;
	char				*comment;
	char				*cor;
	int					cor_len;
	t_label				*label;
	int					line;
	unsigned char		*prog;
	int					prog_size;
}						t_data;

typedef	struct			s_op
{
	char				*name;
	int					param_nbr;
	int					param_type[3];
	char				op_code;
	int					cycles;
	char				*comment;
	int					c1;
	int					c2;
}						t_op;

extern t_op	g_op[];
int						get_params_size_ocp(t_instruc *inst);
void					set_address(t_data *data, char *param,
											char *lbl_name, int inst_pos);
void					set_live(t_data *data, char *param,
											char *lbl_name, int inst_pos);
void					set_special(t_data *data, char *param,
											char *lbl_name, int inst_pos);
void					set_direct(t_data *data, char *param,
											char *lbl_name, int inst_pos);
void					set_indirect(t_data *data, char *param,
											char *lbl_name, int inst_pos);
void					set_register(t_data *data, char *param_1);

int						name_comment_len(int index);
int						parse_nm_cmt(t_data *data, char **s, char *str,
																int index);
char					*name_comment(int index);
void					live_coding_mode(t_data *data, char *filename);
void					write_header(t_data *data);
void					add_to_cor(t_data *data, char c);
void					add_to_prog(t_data *data, unsigned char c);
void					add_param_to_prog(t_data *data, t_instruc *inst,
						char *lbl_name, int inst_pos);
void					print_prog(t_data *data);
void					add_str_to_cor(t_data *data, char *str, int len);
void					set_filename(t_data *data, char *name);
void					set_magic_to_cor(t_data	*data);
void					write_file(t_data *data);
void					add_nm_cmt(t_data *data, char **s, int len, int index);

void					init_data(t_data *data);
void					free_data(t_data *data);
int						is_in_str(char c, char *str);
int						str_is_in_str(char *search, char *str);
char					*ft_pass_space_tab(char *str);
char					*rm_char(char *str, char *rem);
void					free_strsplit(char **arr);
int						set_ocp(int ocp, int index, int val);
int						get_ocp(int ocp, int index);
void					set_register(t_data *data, char *param_1);
void					set_special(t_data *data, char *param, char *lbl_name,
						int inst_pos);
void					set_live(t_data *data, char *param, char *lbl_name,
						int inst_pos);
void					set_direct(t_data *data, char *param, char *lbl_name,
						int inst_pos);
void					set_address(t_data *data, char *param, char *lbl_name,
						int inst_pos);
int						label_exist(t_data *data, char *param_name,
						char *lbl_name);
int						addr_diff(t_data *data, char *lbl_name, int inst_pos);
int						read_name_comment(t_data *data, char *str);
int						routes(t_data *data, char *buf);
void					parser(t_data *data);
void					build(t_data *data);

/*
** Error management:
*/
void					essential_char_in_label_chars(void);
void					error_line(t_data *data, char *err);
void					error_limit(t_data *data, char *err, char *str,
						int limit);
void					error_at(char *err, int line, int column);
void					error_str(t_data *data, char *err, char *str);
void					error(char *err);

/*
** Label and Instructions:
*/
t_label					*lbl_new_elem(char *name);
void					addend_lbl_lst(t_label **lst, t_label *new_elem);
void					print_lbl_lst(t_label *lst);
t_instruc				*inst_new_elem(char *name);
void					addend_inst_lst(t_instruc **lst, t_instruc *new_elem);
void					print_inst_lst(t_instruc *lst);
int						check_add_lbl(char *buf, t_data *data);
int						check_add_lbl_cut(char *buf, char **colon_chr,
						char **sp_lbl_name);
int						check_add_instruc(char *buf, t_data *data);
void					check_all_params(char *trim, char **inst_line, t_data
						*data, int *ret);
int						check_opcode_name(char *str);
int						check_opcode(char *str, t_instruc *inst);
void					check_params(char *str, t_instruc *inst, t_data *data,
						int *order);
void					inst_one_param(char **inst_line, t_data *data);
void					inst_two_params(char **inst_line, char *trim,
						t_data *data);
void					inst_three_params(char **inst_line, char *trim,
						t_data *data);
t_label					*last_label(t_data *data);
char					*real_trim(char *str);
char					*no_comma(char *str);
void					check_first_lbl(t_data *data);
void					if_one_param(int i, t_data *data, t_instruc *inst,
						int *order);
void					if_two_params(int i, t_data *data, t_instruc *inst,
						int *order);
void					two_params_first(int i, t_data *data, t_instruc *inst,
						int *order);
void					two_params_second(int i, t_data *data, t_instruc *inst,
						int *order);
void					if_three_params(int i, t_data *data, t_instruc *inst,
						int *order);
void					three_params_first(int i, t_data *data, t_instruc *inst,
						int *order);
void					three_params_second(int i, t_data *data, t_instruc *inst
						, int *order);
int						three_params_second_cut(t_data *data, t_instruc *inst,
						int *order);
void					three_params_third(int i, t_data *data, t_instruc *inst,
						int *order);
int						is_direct(char *trim, t_data *data, t_instruc *inst,
						int *order);
int						is_indirect(char *trim, t_data *data, t_instruc *inst,
						int *order);
int						is_register(char *trim, t_data *data, t_instruc *inst,
						int *order);
int						without_ocp(char *trim, t_data *data, t_instruc *inst);
int						without_ocp_live(char *trim, t_data *data,
						t_instruc *inst);
void					check_reg(char *str, t_data *data);
void					check_indirect(char *str, t_data *data);
void					check_direct(char *str, t_data *data);
char					*check_comm(char *str, t_data *data);
void					init_check_add_instruc(char ***inst_line, char **trim,
						int *ret);
void					init_check_add_lbl(t_label **new_elem,
						char ***sp_lbl_name, char **colon_chr);
void					free_inst_lbl(t_label *lbl);
void					free_inst_lbl_cut(t_label *tmp_lbl);

#endif
