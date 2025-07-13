/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
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

/* Exit Status Codes (POSIX standard) */
# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_SYNTAX_ERROR 2
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_NOT_EXECUTABLE 126

/* ************************************************************************** */
/*                                 STRUCTURES                                 */
/* ************************************************************************** */

typedef enum t_token_types
{
	TOKEN_NONE,
	TOKEN_WORD,
	TOKEN_COMMAND,
	TOKEN_ARGUMENT,
	TOKEN_FILE,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC
}	t_token_types;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_token
{
	char			*content;
	t_token_types	type;
	struct s_token	*prev;
	struct s_token	*next;
}	t_token;

typedef struct s_shell
{
	t_env	*env;
	int		exit_status;
}	t_shell;

/* ************************************************************************** */
/*                             FUNCTION PROTOTYPES                            */
/* ************************************************************************** */

/* Main functions */
void	init_shell(t_shell *shell, char **envp);
void	shell_loop(t_shell *shell);
void	cleanup_shell(t_shell *shell);
int		process_pipelines(t_shell *shell, t_token *tokens);

/* Shell Input Handling */
char	*read_input_line(void);
int		process_input(t_shell *shell, char *input);
int		handle_input(t_shell *shell, char *input);

/* String Syntax Validation */
int		validate_syntax(char *input);
int		check_quote_matching(char *input);
int		check_operator_syntax(char *input);
int		check_empty_segments(char *input);
void	print_syntax_error(char *error_msg, int position);

/* Environment functions */
t_env	*create_env_node(char *key, char *value);
void	add_env_node(t_env **env, t_env *new_node);
t_env	*find_env_node(t_env *env, char *key);
int		remove_env_node(t_env **env, char *key);
char	*get_env_value(t_env *env, char *key);
int		set_env_value(t_env **env, char *key, char *value);
int		unset_env_value(t_env **env, char *key);
int		env_key_exists(t_env *env, char *key);
void	free_env_node(t_env *node);
void	free_env_list(t_env *env);
int		count_env_nodes(t_env *env);
char	**env_to_array(t_env *env);
t_env	*init_env_from_system(char **envp);

/* Lexer/Tokenizer functions */
int		is_whitespace(char c);
int		is_quote(char c);
int		is_operator_char(char c);
int		is_token_separator(char c);
int		skip_whitespace(const char *str, int *i);
int		is_token_char(char c);

/* Parsing functions */
t_token	*create_token_node(char *content, t_token_types type);
void	add_token_node(t_token **tokens, t_token *new_token);
t_token	*find_token_by_type(t_token *tokens, t_token_types type);
t_token	*get_last_token(t_token *tokens);
int		remove_token_node(t_token **tokens, t_token *token_to_remove);
void	free_token_node(t_token *token);
void	free_tokens(t_token *tokens);
int		count_tokens(t_token *tokens);
int		count_tokens_by_type(t_token *tokens, t_token_types type);
t_token	*duplicate_token_list(t_token *tokens);
int		is_redirect_token(t_token_types type);
int		is_operator_token(t_token_types type);
t_token	*get_next_word_token(t_token *token);
t_token	*get_prev_word_token(t_token *token);
int		validate_token_sequence(t_token *tokens);
t_token	*tokenize(char *input);
t_token	*tokenize_with_expansion(char *input, t_shell *shell);
t_token	*extract_operator(const char *input, int *i);
t_token	*extract_word(const char *input, int *i);
int		count_pipelines(t_token *tokens);
void	cleanup_pipelines(t_token **pipelines, int count);

/* Variable Expansion */
char	*handle_special_vars(char *name, t_shell *shell);
char	*expand_variable(char *var, t_shell *shell);
char	*expand_variables_in_string(char *str, t_shell *shell);
char	*expand_variables_in_string_quoted(char *str, t_shell *shell);
int		find_variable_end(const char *str, int start);
char	*extract_variable_name(const char *str, int start, int end);
char	*replace_in_string(const char *str, int start, int end,
			const char *replacement);
char	**split_expanded_content(char *content);
t_token	*create_tokens_from_words(char **words, t_token_types type);
void	free_word_array(char **words);

/* Quote Handling */
char	*remove_quotes(const char *str);
void	clean_token_quotes(t_token *tokens);

/* Token Classification */
void	classify_tokens(t_token *tokens);

/* Pipeline Parsing */
t_token	**split_by_pipes(t_token *tokens, int *pipeline_count);
void	free_pipeline_array(t_token **pipelines);

/* Print Utils */
void	print_pipeline_tokens(t_token **pipelines, int pipeline_count);

/* Utils */
int		is_builtin(char *cmd);
char	**env_to_array(t_env *env);
void	print_error(char *message);
char	*ft_strndup(const char *s, size_t n);

#endif
