/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:45:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:16:03 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*read_input_line(void)
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

static t_token	**process_tokens(t_shell *shell, char *input, int *pipeline_count)
{
	t_token	*tokens;

	tokens = tokenize_with_expansion(input, shell);
	if (!tokens)
	{
		shell->exit_status = EXIT_FAILURE;
		return (NULL);
	}
	clean_token_quotes(tokens);
	classify_tokens(tokens);
	return (process_pipelines(shell, tokens, pipeline_count));
}

t_token	**process_input(t_shell *shell, char *input, int *pipeline_count)
{
	printf("Processing: %s\n", input);
	if (validate_syntax(input) == FAILURE)
	{
		shell->exit_status = EXIT_SYNTAX_ERROR;
		return (NULL);
	}
	return (process_tokens(shell, input, pipeline_count));
}

t_token	**handle_input(t_shell *shell, char *input, int *pipeline_count)
{
	if (ft_strlen(input) == 0)
	{
		shell->exit_status = 0;
		return (NULL);
	}
	return (process_input(shell, input, pipeline_count));
}
