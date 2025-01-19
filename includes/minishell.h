/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:11:33 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/19 16:21:29 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

enum					e_type
{
	COMMAND,
	ARG,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	IN_FILE,
	OUT_FILE,
	HEREDOC_DELIMITER,
	APPEND,
	HEREDOC,
};

typedef struct s_node
{
	char				*value;
	int					type;
	struct s_node		*prev;
	struct s_node		*next;
}						t_node;

typedef struct s_list
{
	int					len;
	t_node				*head;
	int					fd[2];
	struct s_list		*prev;
	struct s_list		*next;
}						t_list;

typedef struct s_tab
{
	t_list				*head;
	int					len;
}						t_tab;

typedef struct s_envnode
{
	char				*key;
	char				*value;
	struct s_envnode	*prev;
	struct s_envnode	*next;
}						t_envnode;

typedef struct s_env
{
	int					len;
	t_envnode			*head;
	t_envnode			*tail;
}						t_env;

typedef struct s_main
{
	t_env				*envp_list;
	char				**envp;
	t_tab				*cmdtab;
	int					fd[2];
}						t_main;

// DISPLAY_PROMPT.C -----------------------------------------------------------
char					*read_input(char *user_input);

// VALIDATE_INPUT.C -----------------------------------------------------------
bool					validate_input(char *input);
bool					check_unclosed_quotes(char *s);
bool					has_only_spaces(char *input);

// ENV.C -----------------------------------------------------------------------
t_envnode				*new_envnode(char *envp);
void					addback_env(t_envnode *newnode, t_env *list);
t_env					*get_env_list(char **envp);
int						ft_env(t_env *env);
int						ft_export(char **args, t_env *env);
int						ft_unset(char **args, t_env *env);
int						free_env(t_env *env);
int						ft_exit(char **args, t_main *main);
int						ft_exit_nbr(int nbr, t_main *main);
int						str_isname(char *str);
void					update_env(char *key, char *value, t_env *envp);
void					update_envnode(char *value, t_envnode *node);

// EXECUTOR.C ------------------------------------------------------------------
void					execute_commands(t_main *main);
int						execute_builtins(t_list *cmdlist, t_main *main);
void					execute_external_command(t_list *cmdlist, char **envp);
int						execute_fork_commands(t_main *main);
t_node					*get_cmd(t_list *cmdlist);

// PRINT.C ---------------------------------------------------------------------
void					print_split(char **array);
void					print_list(t_list *list);
void					print_tab(t_tab *table);

// FREE.C ---------------------------------------------------------------------
void					free_split(char **array);
void					free_table(t_tab *cmdtable);
int						free_env(t_env *env);
void					free_list(t_list *cmdline);
void					free_envnode(t_envnode *node);
void					free_main(t_main *main);

// IDENTIFY_CHAR.C ------------------------------------------------------------
int						is_operator(char c);
int						is_quote(char c);
int						is_space(char c);
int						is_metachar(char c);

// LEXER.C --------------------------------------------------------------------
/*
 * count the amount of tokens in an input
 */
int						count_tokens(char *input);
char					**metachar_split(char *user_input);

/*
* splits user_input into an array of tokens.
* lexical analisis divides tokens by: >, <, |, <<, >>, '...',
	"..." and SPACE getcwd(buf, 0);
*/
char					**get_tokens(char *user_input);

// LEXER_UTILS.C --------------------------------------------------------------
char					*strtrim_space(char *s1);
char					*substr_by_address(char *str, int len);

// UTILS.C ---------------------------------------------------------------------
int						ft_error(char *cmd, char *arg, char *message, int ret);
int						str_isname(char *str);
int						split_len(char **split);

/*
* ft_substr but starting by the first index of str
*/
char					*substr_by_address(char *str, int len);

// TOKENIZER.C ----------------------------------------------------------------
t_tab					*get_cmdtable(char **input, t_env *env);
void					identify_tokens(t_tab *cmdtable);
void					get_type(t_node *token);
void					get_redirect_type(t_node *token);

// TOKENIZER_UTILS.C ----------------------------------------------------------
int						cmdlen(char **input);
void					add_node(t_node *newnode, t_list *list);
void					add_list(t_list *newnode, t_tab *cmdtable);
t_node					*new_node(char *token);
t_list					*new_list(char **input);

// TOKEN_FORMAT.C ------------------------------------------------------------
void					rm_quote(t_node *token);
void					format(t_tab *cmdtable, t_env *env);
t_envnode				*search_key(t_env *list, char *key);
int						strlen_isname(char *str);
char					*ft_strfjoin(char *s1, char *s2);
int						is_name(char c);

// ft_echo.C ---------------------------------------------------------------------
int						ft_echo(char **arg);

// ft_cd.C ----------------------------------------------------------------------
char					*get_key_value(t_env *list, char *key);
void					update_key_value(t_env *list, char *key, char *new_val);
int						ft_cd(char **args, t_env *env);
int						ft_error(char *cmd, char *arg, char *message, int ret);
int						split_len(char **split);

// ft_pwd.C -----------------------------------------------------------------------
int						ft_pwd(void);

// redirect.c
int						redirect(t_list *cmdlist);

// convertions.c
char					**env_to_char_array(t_env *envp);
char					**list_to_char_array(t_node *token);

#endif
