/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/04 16:50:00 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*                                  INCLUDES                                  */
/* ************************************************************************** */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

/* ************************************************************************** */
/*                                  DEFINES                                   */
/* ************************************************************************** */

# define PROMPT "minishell$ "
# define SUCCESS 0
# define FAILURE 1

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef enum e_token_types
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
} e_token_types;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*content;
	e_token_types	type;
    struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			**args;
	char			*input_file;
	char			*output_file;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_env	*env;
	t_cmd	**commands;
	int		exit_status;
}	t_shell;

/* ************************************************************************** */
/*                             FUNCTION PROTOTYPES                            */
/* ************************************************************************** */

/* Main functions */
void	init_shell(t_shell *shell, char **envp);
void	shell_loop(t_shell *shell);
void	cleanup_shell(t_shell *shell);

/* Environment functions */
t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **env, t_env *new_node);
char	*get_env_value(t_env *env, char *key);
void	set_env_value(t_env **env, char *key, char *value);
void	free_env_list(t_env *env);

/* Parsing functions */
t_token	*tokenize(char *input);
t_cmd	*parse_tokens(t_token *tokens);
void	free_tokens(t_token *tokens);
void	free_commands(t_cmd *commands);


/* Execution functions */
int		execute_commands(t_shell *shell);
int		execute_builtin(t_shell *shell, t_cmd *cmd);
int		execute_external(t_shell *shell, t_cmd *cmd);

/* Built-in commands */
int		builtin_echo(char **args);
int		builtin_cd(t_shell *shell, char **args);
int		builtin_pwd(void);
int		builtin_export(t_shell *shell, char **args);
int		builtin_unset(t_shell *shell, char **args);
int		builtin_env(t_shell *shell);
int		builtin_exit(t_shell *shell, char **args);

/* Utils */
int		is_builtin(char *cmd);
char	**env_to_array(t_env *env);
void	print_error(char *message);
char	*ft_strndup(const char *s, size_t n);


#endif
