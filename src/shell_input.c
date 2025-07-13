/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:45:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
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

static int	process_tokens(t_shell *shell, char *input)
{
	t_token	*tokens;

	tokens = tokenize_with_expansion(input, shell);
	if (!tokens)
	{
		shell->exit_status = EXIT_FAILURE;
		return (FAILURE);
	}
	clean_token_quotes(tokens);
	classify_tokens(tokens);
	return (process_pipelines(shell, tokens));
}

int	process_input(t_shell *shell, char *input)
{
	printf("Processing: %s\n", input);
	if (validate_syntax(input) == FAILURE)
	{
		shell->exit_status = EXIT_SYNTAX_ERROR;
		return (FAILURE);
	}
	return (process_tokens(shell, input));
}

int	handle_input(t_shell *shell, char *input)
{
	if (ft_strlen(input) == 0)
	{
		shell->exit_status = 0;
		return (FAILURE);
	}
	process_input(shell, input);
	return (SUCCESS);
}
