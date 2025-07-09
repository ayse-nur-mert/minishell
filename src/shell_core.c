/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 15:53:26 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */

#include "../lib/minishell.h"

void	init_shell(t_shell *shell, char **envp)
{
	if (!shell)
		return ;
	shell->env = init_env_from_system(envp);
	shell->exit_status = 0;
}

void	cleanup_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->env)
		free_env_list(shell->env);
}

static char	*read_input_line(void)
{
	char	*input;

	input = readline(PROMPT);
	if (!input)
	{
		printf("exit\n");
		return (NULL);
	}
	if (*input)
		add_history(input);
	return (input);
}

static void	print_tokens(t_token *tokens)
{
	t_token	*current;
	
	current = tokens;
	while (current)
	{
		printf("Token: [%s] Type: ", current->content);
		if (current->type == TOKEN_NONE)
			printf("NONE");
		else if (current->type == TOKEN_WORD)
			printf("WORD");
		else if (current->type == TOKEN_COMMAND)
			printf("COMMAND");
		else if (current->type == TOKEN_ARGUMENT)
			printf("ARGUMENT");
		else if (current->type == TOKEN_FILE)
			printf("FILE");
		else if (current->type == TOKEN_PIPE)
			printf("PIPE");
		else if (current->type == TOKEN_REDIRECT_IN)
			printf("REDIRECT_IN");
		else if (current->type == TOKEN_REDIRECT_OUT)
			printf("REDIRECT_OUT");
		else if (current->type == TOKEN_APPEND)
			printf("APPEND");
		else if (current->type == TOKEN_HEREDOC)
			printf("HEREDOC");
		printf("\n");
		current = current->next;
	}
}

static int	process_input(t_shell *shell, char *input)
{
	t_token	*tokens;
	
	printf("Processing: %s\n", input);
	// mesaj çıktıları düzenlenecek
	if (validate_syntax(input) == FAILURE)
	{
		shell->exit_status = EXIT_SYNTAX_ERROR;
		return (FAILURE);
	}

	tokens = tokenize(input);
	if (!tokens)
	{
		shell->exit_status = EXIT_FAILURE;
		return (FAILURE);
	}	
	print_tokens(tokens);
	free_tokens(tokens);
	shell->exit_status = EXIT_SUCCESS;
	return (SUCCESS);
}

void	shell_loop(t_shell *shell)
{
	char	*input;

	if (!shell || !shell->env)
	{
		shell->exit_status = 1;
		return ;
	}
	while (1)
	{
		input = read_input_line();
		if (!input)
		{
			shell->exit_status = 0;
			break ;
		}
		if (ft_strlen(input) == 0)
		{
			free(input);
			shell->exit_status = 0;
			continue ;
		}
		process_input(shell, input);
		free(input);
		printf("\n");
	}
}
