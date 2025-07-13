/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_core.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:16:11 by amert            ###   ########.fr       */
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

t_token	**process_pipelines(t_shell *shell, t_token *tokens, int *pipeline_count)
{
	t_token	**pipelines;

	pipelines = split_by_pipes(tokens, pipeline_count);
	if (!pipelines)
	{
		free_tokens(tokens);
		shell->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	printf("=== After Pipeline Splitting ===\n");
	print_pipeline_tokens(pipelines, *pipeline_count);
	free_tokens(tokens);
	shell->exit_status = EXIT_SUCCESS;
	return (pipelines);
}

void	shell_loop(t_shell *shell)
{
	char		*input;
	t_token		**pipelines;
	int			pipeline_count;

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
		pipelines = handle_input(shell, input, &pipeline_count);
		if (pipelines)
		{
			free_pipeline_array(pipelines);
			printf("\n");
		}
		free(input);
	}
}
