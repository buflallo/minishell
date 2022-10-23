/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hlachkar <hlachkar@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 18:20:30 by fahd              #+#    #+#             */
/*   Updated: 2022/10/19 16:36:29 by hlachkar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <ctype.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <stdio.h>
# include <stddef.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lexer
{
	char	*str;
	char	c;
	int		i;
}			t_lexer;

typedef struct s_token
{
	char			*val;
	int				flag;
	struct s_token	*next;
	enum
	{
		WORD,
		DQUOTE,
		SQUOTE,
		BACKSLASH,
		PIPE,
		GREATANDGREAT,
		LESSANDLESS,
		GREAT,
		LESS,
		DOLLAR,
		END,
	} e_type;
}		t_token;

typedef struct s_redir
{
	char			*file;
	int				e_type;
	int				fdout;
	int				fdin;
	struct s_redir	*next;

}		t_redir;

typedef struct s_parse
{
	char			*cmd;
	char			**argv;
	t_redir			*redir;
	struct s_parse	*next;
}		t_parse;

typedef struct s_env
{
	char			*key;
	char			*val;
	char			sep;
	struct s_env	*next;
}		t_env;

typedef struct s_minishell
{
	char	*line;
	int		exit_status;
	int		exit_sig;
	int		g_err;
	pid_t	pid;
	void	*alloc[1000000];
	int		index;
	t_env	*my_env;
}		t_minishell;

t_minishell	g_vars;

void print_tokens(t_token *tokens);
t_lexer	*ft_init_lexer(char *str, char c);
t_lexer	*advance_lexer(t_lexer *lexer);
t_token	*send_lexer_to_tokenize(t_lexer *lexer);
t_token	*init_token(char *val, int type);
t_token	*lst_add_back(t_token *lst, t_token *new);
t_parse	*init_command(void);
t_parse	*add_command(t_parse *commad);
t_parse	*lst_add_back_command(t_parse *lst, t_parse *new);
t_redir	*add_redir(t_redir *redir, char *val, int type);
t_redir	*init_redir(char *val, int type);
void	dup_files(int exe, int fin, int fout);
void	file_error(char *filename);
void	tokenize_pipe(t_token **tmp, t_lexer *lexer);
void	tokenize_in_redir(t_token **tmp, t_lexer *lexer);
void	tokenize_squote(t_token **tmp, t_lexer *lexer);
void	tokenize_word(t_token **tmp, t_lexer *lexer);
void	tokenize_dollar(t_token **tmp, t_lexer *lexer);
void	tokenize_dquote(t_token **tmp, t_lexer *lexer);
void	tokenize_out_redir(t_token **tmp, t_lexer *lexer);
void	tokenize_end(t_token **tmp);
t_env	*lst_new(char *key, char sep, char *val);
char	*ft_strsub(t_lexer *lexer, size_t len);
int		ft_strnstr(const char *str, const char *to_find, size_t len);
char	*ft_strcharjoin(char *s1, char c);
char	*ft_substr(char *s, unsigned int start, size_t len);
void	ft_putnbr_fd(int n, int fd);
int		ft_is_space(void);
char	*ft_itoa(int n);
int		ft_isspace(int c);
int		ft_isalpha(int c);
void	check_cmd(t_parse *cmd);
char	*ft_lowercase(char *str);
int		check_minus(char *arg, char c);
int		str_digit(char *str);
int		str_is_alnum(char *str);
int		ft_isdigit(int c);
int		ft_isalnum(int c);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *s1);
int		ft_strlen(char *s);
void	*f_malloc(size_t size);
char	*ft_strjoin(char *s1, char *s2, int fr);
char	*jme3arg(t_token **b, int exec, int ch_d);
size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize);
char	*join_3_str(char *s1, char *s2, char *s3);
void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *s, int fd);
char	*ft_strchr(const char *str, int c);
int		ft_int_strchr(const char *s, int c);
int		token_index(char *str);
int		lst_size(t_token *b);
void	*realloc_array(char **arg, char *str);
void	print_l(t_parse *lst);
void	create_commands(t_token *token, t_parse **command);
char	*expand_dollar(char *dq_content, int exec);
int		exec_builtins(t_parse *commands, t_env **my_env);
void	exec_pipeline(t_parse *commands, t_env **env);
int		array_size(char **str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin1(char *s1, char *s2, int c);
int		pwd(void);
void	free_2(char **tmp);
int		env(void);
void	errors(int exitt);
int		str_sp_chr(char *str);
char	*check_sp_chr(t_token *b);
char	*dollar_q_d(t_token **b);
char	*dollar_qu(t_token **b, int exec, char *str);
char	*normal_expansion(t_token **b, int f);
void	checkin_dollar(t_token **b, char **str, int ch_d);
void	init_env(char **env);
int		ft_is_ex_token(char c);
char	*ft_strcpy(char *dest, char *src);
char	*my_getenv(t_env *env, char *key);
char	*my_getenv_key(t_env **env, char *key);
void	update_export(t_env **env, char *key, char sep, char *val);
char	*get_path(char *cmd, char **env);
void	execute(t_parse *command, t_env **env);
int		check_exp_arg(char *to_check);
int		builtins_cases(t_parse *cmd);
int		cd(t_parse *head, t_env *my_env);
void	lst_add_backenv(t_env **lst, t_env *new);
int		export(t_parse *head);
void	check_numb(char *str);
int		my_exit(t_parse *cmd);
int		echo(t_parse *cmd);
char	*if_only_dollar(t_lexer *lexer);
int		unset(t_parse *cmd);
void	wrong_cmd(char *cmd);
void	wrong_cmd_helper(char *error, int w);
void	c_signal(void);
void	open_redir(t_parse *head, int exec);
void	pipe_redir(t_parse *cmd, int in, int index, int *fd);
int		simple_cmd(t_parse *cmd);
int		is_piped(void);
void	read_heredocs(t_parse *command);
int		only_enter(void);
int		ft_is_space(void);
#endif
