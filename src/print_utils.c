/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:30:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	print_token_type(t_token_types type)
{
	if (type == TOKEN_NONE)
		printf("NONE");
	else if (type == TOKEN_WORD)
		printf("WORD");
	else if (type == TOKEN_COMMAND)
		printf("COMMAND");
	else if (type == TOKEN_ARGUMENT)
		printf("ARGUMENT");
	else if (type == TOKEN_FILE)
		printf("FILE");
	else if (type == TOKEN_PIPE)
		printf("PIPE");
	else if (type == TOKEN_REDIRECT_IN)
		printf("REDIRECT_IN");
	else if (type == TOKEN_REDIRECT_OUT)
		printf("REDIRECT_OUT");
	else if (type == TOKEN_APPEND)
		printf("APPEND");
	else if (type == TOKEN_HEREDOC)
		printf("HEREDOC");
}

static void	print_pipeline_tokens_single(t_token *tokens, int pipeline_num)
{
	t_token	*current;

	printf("=== Pipeline %d ===\n", pipeline_num);
	current = tokens;
	while (current)
	{
		printf("Token: [%s] Type: ", current->content);
		print_token_type(current->type);
		printf("\n");
		current = current->next;
	}
}

void	print_pipeline_tokens(t_token **pipelines, int pipeline_count)
{
	int	i;

	i = 0;
	while (i < pipeline_count)
	{
		print_pipeline_tokens_single(pipelines[i], i + 1);
		i++;
	}
}
