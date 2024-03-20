/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlorion <nlorion@42.student.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 12:42:17 by avassor           #+#    #+#             */
/*   Updated: 2023/04/22 12:59:49 by nlorion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// ......................... INCLUDES ................................ //

# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./../libft/libft.h"

// ......................... DEFINE ......................................

# define EOL -1
# define EOT -2
# define SYNTAX 130
# define EXPORTVAR 132
# define BUFFER_SIZE 1

// ......................... GLOBAL VAR ....................................

extern int	g_status;

// ......................... TOKEN ENUM ....................................

typedef enum e_lxid
{
	END = '\0',
	CSPACE = ' ',
	SMPLQUOT = '\'',
	ENV = '$',
	DBLQUOT = '\"',
	DOT = '.',
	SLASH = '/',
	LESS = '<',
	GREATR = '>',
	INTER = '?',
	PIPE = '|',
	CHAR = -1,
	HEAD = -42,
	NOMTCH = 128
}	t_lxid;

// ......................... LEXER STRUCTURE ................................ //

typedef struct s_lxr
{
	struct s_env	*env;
	char			*buff;
	char			*data;
	int				size;
	int				pos;
	int				pos_data;
	t_lxid			last_id;
	t_lxid			prev_id;
}	t_lxr;

// ......................... TOKEN STRUCTURE ................................ //

typedef struct s_tkn
{
	char			*data;
	int				size;
	t_lxid			id;
	struct s_tkn	*prev;
	struct s_tkn	*next;
	_Bool			err;
}	t_tkn;

// // ......................... PARSE ENUM ....................................

typedef enum e_node_type
{
	N_CMD = 1,
	N_PIPE
}	t_node_type;

// // ......................... PARSE STRUCTURE ...............................

typedef struct s_tkn_analysis
{
	_Bool	pipe;
	size_t	pipes;
	_Bool	redir;
	size_t	in_redir;
	size_t	out_redir;
	size_t	appen_redir;
	size_t	here_doc;
}	t_tkn_analysis;

typedef union u_node_ptr
{
	struct s_node_cmd	*com;
	struct s_node_pipe	*pip;
}	t_node_ptr;

typedef struct s_node
{
	enum e_node_type	type;
	union u_node_ptr	*data;
}	t_node;

typedef struct s_node_pipe
{
	struct s_node	*in;
	struct s_node	*out;
	struct s_node	*prev;
}	t_node_pipe;

typedef struct s_node_cmd
{
	char			**cmd;
	size_t			matrix_size;
	_Bool			file;
	_Bool			here_doc;
	_Bool			in;
	_Bool			out;
	_Bool			appen;
	_Bool			path;
	_Bool			env;
	_Bool			quotes;
	_Bool			state;
	t_node			*pipe_parent;
	struct s_excmd	*excmd;
	t_tkn_analysis	*tkn;
}	t_node_cmd;

typedef struct s_excmd
{
	size_t			in_size;
	size_t			out_size;
	size_t			appen;
	size_t			heredoc;
	_Bool			enomem;
	struct s_lcmd	*in;
	struct s_lcmd	*cmd;
	struct s_lcmd	*out;
}	t_excmd;

typedef struct s_lcmd
{
	char			*data;
	struct s_lcmd	*prev;
	struct s_lcmd	*next;
}	t_lcmd;

typedef struct s_trunk
{
	t_tkn				*tkn;
	t_tkn_analysis		*an;
	size_t				size;
	struct s_node		*leafs;
	struct s_exec		*exec;
	struct s_env		*envp;
}	t_trunk;

typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

// ......................... EXEC STRUCTURE ................................. //

typedef struct s_exec
{
	struct s_env	*envp;
	char			**chenv;
	char			**path;
	int				pipes;
	int				*fd;
	int				pid;
	int				in;
	int				out;
	int				hd;
	int				hd_err;
	struct stat		s_buf;
}	t_exec;

// ......................... MINISHEL FUNCTIONS ............................. //

int				minishell(t_lxr *lxr, t_env *envp, char **arrenv);
void			rror(int r_no);
t_lxr			*init_lxr(t_lxr *lxr);
size_t			cleanr(t_trunk *tree, t_tkn *tkn, t_lxr *lxr);
void			free_tkn(t_tkn *tkn);
void			free_trunk_root(t_trunk *tree);
void			free_matrix(char **cmd, size_t matrix);
t_node			*free_cmd(t_node *node);
void			free_tree(t_trunk *tree);
size_t			chk_osp(char *line);
size_t			chk_opp(char *tmp);
void			free_list(t_excmd *excmd);
void			free_link(t_lcmd *list);
void			good_bye(t_lxr *lxr, t_env *mini_env);
void			rrdir(_Bool i);
t_env			*term_exec(t_lxr *lxr, t_env *mini_env);

// ......................... PARSE FUNCTIONS ................................ //

t_node_cmd		*build_cmd(t_tkn *tkn);
t_trunk			*build_tree(t_tkn *tkn, t_env *envp);
t_trunk			*build_trunk(t_tkn *tkn);
char			*ft_realloc(char *in, int size);
void			ft_strcpy(char *in, char *out, size_t size);
void			ft_nullset(char *in, int size);
void			get_redir_type(t_tkn_analysis *an, t_tkn *tkn);
_Bool			check_tkn_type(t_node_cmd *cmd, t_tkn *tkn);
_Bool			check_here(t_tkn *tkn);
_Bool			check_app(t_tkn *tkn);
_Bool			check_in(t_tkn *tkn);
_Bool			check_out(t_tkn *tkn);
t_tkn			*build_node(t_trunk *trunk, t_tkn *tkn);
t_tkn			*get_next_tkn(t_tkn *tkn, t_lxid id);
char			**ft_add_dim(char **array, char *str, size_t i);
char			**get_data(t_node_cmd *cmd, t_tkn *tkn);
_Bool			place_in_tree(t_trunk *trunk, t_node *node);
_Bool			build_pipe(t_trunk *trunk);
t_tkn			*build_node(t_trunk *trunk, t_tkn *tkn);
void			print_tree(t_trunk *trunk);
size_t			check_redir(t_node_cmd *cmd, t_tkn *tkn);
size_t			get_matrix_size(t_tkn *tkn);
char			*add_to_matrix(char *tkn);
size_t			redir_ok(t_node_cmd *cmd, t_tkn *tkn);
char			*empty_env(char *tmp);
size_t			illegal_redir(char *line);
size_t			check_red(t_node *cmd);
size_t			check_pipes(t_node *cmd);
size_t			check_quotes(t_node *cmd);
size_t			chk_unclosed_quotes(char *line);
_Bool			clear_empty_quotes(t_node *cmd);
char			**delete_dim(t_node *cmd, size_t i);
_Bool			syntaxr(t_node *node, t_env *envp);
_Bool			swap_array(t_node *cmd, int i);
void			unquote(t_node *cmd);
void			do_unquote(t_lcmd *lcmd);
char			*remove_quote(char *cmd);
_Bool			interpretr(t_node *cmd);
void			get_status(t_excmd *head, char **cmd);
_Bool			swap_index(t_lcmd *lcmd, char *in);
size_t			add_to_list(t_lcmd *init, char **in);
t_lcmd			*extract_data(t_excmd *head, char **cmd, char c, size_t msize);
t_lcmd			*add_to_cmd_list(t_lcmd *cmd, char *in);
_Bool			build_link(t_node *node, char **cmd);
t_excmd			*init_excmd(void);
t_lcmd			*init_lcmd(size_t *i, _Bool *sig);
void			clear_spaces(t_node *cmd);
void			print_linked_list(t_trunk *tree);
void			update_heads(t_node *cmd);
t_lcmd			*undo_link(t_lcmd *ptr);
char			*catch_env(t_env *envp, char *env);
char			*find_env_name(char *envp);
size_t			illegal_line(char *line);
_Bool			chk_morrrr(t_node_cmd *cmd, t_tkn *tkn);
char			**init_var(int *i, t_node *cmd);
int				do_clear_empty(t_node *cmd, char **ptr, int i);
_Bool			end_link(t_node *node, t_excmd *head, char **cmd);
int				extract_cmd(t_node *node, t_excmd *head, char **cmd);
_Bool			free_dim(char **cmd, size_t size);
_Bool			chk_chr(char c);
t_env			*build_env(char **envp);
t_env			*get_last_env(t_env *head);
t_env			*extract_env(char *env);
char			*find_env_data(char *envp);
void			free_env(t_env *head);
char			*cut_env(char *env);
char			*write_expand_env(char *dbl, char *env, char *ptr, size_t size);
_Bool			do_expand(char **browse, t_env *envp);
_Bool			do_expand_dbl(char **browse, size_t i, t_env *envp);
_Bool			expandr(t_node *node, t_env *envp);
t_node			*get_next_cmd_node(t_node *node);
char			*expand_env(char *env, t_env *envp);
char			*expand_dbl_quotes(char *dbl, t_env *envp);
t_tkn			*tkn_err(void);
void			pipe_placer(t_trunk *trunk, t_node *node);
t_lxid			get_id(t_lxid id, char *str);
int				empty_quotes(t_node *cmd, char **ptr);
_Bool			buff_err(char *buff);
int				shift_index(t_node *cmd, char **ptr);
_Bool			is_echo(char **ptr);
void			clear_spaces_echo(t_node *cmd, char **ptr);
size_t			shift_echo(t_node *cmd, char **ptr);
void			extract_echo(t_lcmd *head);
_Bool			ft_sprstrncmp(char *s1, char *s2);
_Bool			group_cmd(t_node *cmd);
char			*join_cmd(char *str1, char *str2);
void			swift_index(t_node *cmd, char **ptr);
void			update_indexes(t_node *cmd);
int				groupamargue(t_node *cmd, char **ptr, int i);
void			clear_null(t_node *cmd);
_Bool			chkcmd(t_node *node, char **cmd);
void			kill_sp(t_node *cmd, char **ptr);
char			*clear_empty_env(char *dbl, char *tmp);
char			*delete_env(char *tmp, size_t i);
_Bool			group_redir(t_node *cmd);
void			grouper(t_node *cmd, char **ptr);
_Bool			chk_redir_data(char **ptr);
void			init_extract(size_t *size, size_t *i, int *wrk);
int				clearrr(t_node *cmd, char **ptr, int i);
void			clear_me(t_node *cmd, char **ptr);
char			*expand_dbl(t_env *envp, char *ptr, char *tmp, char *rec);
char			*replace_env(char *dbl, char *ptr, t_env *envp);
char			*op_clear(char *new, char *dbl, size_t i, size_t j);
size_t			op_del(char *new, char *tmp, size_t m, size_t i);
void			prer(size_t id);
_Bool			buff_r1(char *buff, int i);
_Bool			buff_err(char *buff);
size_t			chk_opp(char *tmp);
size_t			chk_op1(char *tmp, size_t i);
size_t			chk_op2(size_t pp);
t_tkn_analysis	*tkn_analyzr(t_tkn *tkn);
t_env			*empty_varg(t_env *head);
char			*wrt(char *to);
void			end_varg(t_env *head);
_Bool			chk_fnl(t_node *cmd);
_Bool			chk_fcmd(t_node *cmd);
_Bool			chk_ill(char *data, char c);
void			del_chr(char *data, char c);
void			chk_ill2(char *data);

// ......................... TOKEN FUNCTIONS ................................

t_tkn			*tknize(t_lxr *lxr);
int				init_buff(t_lxr *lxr);
int				add_buff(t_lxr *lxr, char c);
int				add_find_id(t_lxr *lxr, t_lxid id);
t_tkn			*new_tkn(t_lxr *lxr, char *str, t_lxid id, t_tkn *tkn);
t_tkn			*tknize(t_lxr *lxr);
void			free_tkn(t_tkn *tkn);
int				add_end(t_lxr *lxr, t_lxid id);
t_tkn			*init_head(t_lxr *lxr);
int				init_buff(t_lxr *lxr);
int				find_id(t_lxr *lxr, t_lxid id);
int				trig_char(t_tkn *head, t_lxr *lxr, t_lxid id);
int				add_buff_lim(t_lxr *lxr, t_lxid c);
int				skip_trig(t_lxr *lxr, t_lxid id);
void			tkn_add_back(t_tkn *head, t_tkn *new);
int				add_path(t_lxr *lxr, t_lxid id);
size_t			check_even_id(char *str, t_lxid id);
int				nomtch(t_lxr *lxr, t_lxid id);
int				add_env(t_lxr *lxr, t_lxid id);
t_tkn			*get_last_tkn(t_tkn *tkn);

// ......................... LEXER FUNCTIONS .................................

char			prev_next_chr(t_lxr *lxr, int pos);
void			skip_wspaces(t_lxr *lxr);
void			unget_chr(t_lxr *lxr);
char			next_chr(t_lxr *lxr);
t_lxid			lxr_id(char c);
char			prev_ious_chr(t_lxr *lxr, int pos);

// ......................... EXEC FUNCTIONS ...............................

t_exec			*exec_init(t_trunk *trk, t_env *envp, char **arrenv);
_Bool			file_opener(t_excmd *curr, int fd[2]);
int				execute(t_trunk *tree, t_env *envp, char **arrenv);
_Bool			check_builtin(t_excmd *excmd);
int				create_file_in(t_excmd *curr);
int				create_file_out(t_excmd *curr);
int				exec_builtin(t_trunk *trk, t_exec *exec,
					t_excmd *curr, t_lxr *lxr);
int				ft_run(t_exec *exec, t_excmd *curr, int *fd);
char			**split_path(t_env *envp);
_Bool			chk_pipe_next(t_excmd *next);
int				display_status(t_exec *exec, t_excmd *curr);
char			*ft_getenv_data(t_exec *exec, char *id);
char			*get_system_path(t_exec *exec, char *cmd);
char			*add_dir(char *content, char *cmd);
char			*get_user_path(char *cmd, t_exec *exec);
char			*get_path(t_exec *exec, char *cmd);
char			**get_args(t_excmd *curr, t_lcmd *lcmd);
char			*build_args(t_lcmd *lcmd, int i);
int				read_doc(char *cut);
void			fd_init(t_exec *exec, int fd[2]);
int				pied_piper(t_exec *exec, int i);
void			get_fd(t_exec *exec, int fd[2], int i);
void			std_fd(int fd[2]);
size_t			get_matrix_2(char **args);
int				no_such(char *str);
void			close_fd(int fd, int ref);
void			free_exec(t_exec *exec);
void			runnin(char *run, char **args, char **chenv);
void			close_fds(t_exec *exec);
int				is_redir(t_excmd *curr, int *fd);
int				child_process(t_exec *exec, t_excmd *curr, char *run,
					char **args);
_Bool			mng_here_doc(t_exec *exec, t_node *cmd);
_Bool			go_and_read(t_exec *exec, t_excmd *curr);
char			*create_file_here(t_exec *exec, char *c);
char			*open_doc(t_exec *exec, char *file, char *c);
char			*update_redir(t_exec *exec, char *file, char *c);
void			here_doc_msg(char *c, char *stream);
void			hd_sig_line(int nb);
void			exec_end(t_exec *exec, t_trunk *tree, t_env *envp);
void			free_here_doc(t_exec *exec, t_node *node);
int				hd_quit(int dupl, char *stream, char *c, t_exec *exec);

// ......................... BUILTIN FUNCTIONS .............................

int				count_cmd(t_excmd *curr);
size_t			search_str(const char *s, int c);
int				ft_strcomp(const char *s1, const char *s2);
int				print_echo_1(t_excmd *curr);
char			*concate_dir(char *s1, char *s2);
int				ft_display_env(t_trunk *tree);
int				ft_cd_1(t_excmd *curr, t_exec *exec);
int				ft_unset(t_exec *exec, t_excmd *curr);
int				ft_pwd(void);
_Bool			print_env(t_exec *exec);
_Bool			ft_export(t_exec *exec, t_excmd *excmd);
_Bool			chk_env_name(char *name, t_env *envp);
_Bool			add_env_list(t_env *envp, char *name, char *data);
_Bool			do_export(t_exec *exec, t_lcmd *cmd, char *name, char *data);
char			*export_data(char *cmd);
char			*export_name(char *cmd);
_Bool			chk_equal(t_lcmd *cmd);
int				numlen(long long int val);
long long int	ft_atol(const char *value);
int				is_numeric(char *str);
int				exec_buil_pipe(t_exec *exec, t_excmd *curr, int fd[2], int i);
_Bool			ft_run_built_2(t_exec *exec, t_excmd *curr, int fd[2], int i);
char			*write_data(char *data, size_t i, t_lcmd *tmp);
char			*fill_data(char *cmd, size_t i, size_t j, size_t *k);
void			free_cd(char *root, char *cd_env);
void			follow_export(t_exec *exec, t_lcmd *cmd);

// ..................... SIGNALS ..........................................

void			child_signal(int num);
void			sig_clean(int nope);
void			sig_init(void);
void			sig_child(void);
int				run_signals(int num);

// ..................... MANAGE ERROR .....................................

int				return_error(char *cmd, char *msg, int status);
int				return_code(void);
int				check_err(t_excmd *curr);
int				has_perm(char **path, char *bin, struct stat s_buf);

// ..................... GNL ..............................................

typedef struct s_stash
{
	char			*str;
	struct s_stash	*next;
}	t_stash;

char			*get_next_line(int fd, char *lim);
void			ft_reader(int fd, t_stash **stash);
void			ft_addline(t_stash *stash, char **line);
void			ft_addbuff(char *buf, t_stash **stash, int i);
void			ft_recover(t_stash **stash);
size_t			line_chk2(char *a, char *b);
char			*limited(t_stash **stash, char *line, int fd);
void			ft_left(t_stash **stash, t_stash *new, char *p1, char *p2);
int				ft_scanner(t_stash *stash);
t_stash			*ft_lst_get_last(t_stash *stash);
void			ft_unleash(t_stash *stash);
int				ft_linkbrows(t_stash *stash);

#endif
