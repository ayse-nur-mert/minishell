/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:10:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 14:10:00 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static t_token	*create_and_add_token(t_token **new_list, t_token *current)
{
	t_token	*new_token;

	new_token = create_token_node(current->content, current->type);
	if (!new_token)
	{
		free_tokens(*new_list);
		return (NULL);
	}
	add_token_node(new_list, new_token);
	return (new_token);
}

static t_token	*copy_tokens_until_pipe(t_token *start, t_token **next_start)
{
	t_token	*new_list;
	t_token	*current;

	new_list = NULL;
	current = start;
	while (current && current->type != TOKEN_PIPE)
	{
		if (!create_and_add_token(&new_list, current))
			return (NULL);
		current = current->next;
	}
	if (current && current->type == TOKEN_PIPE)
		*next_start = current->next;
	else
		*next_start = NULL;
	return (new_list);
}

static t_token	**allocate_pipelines(int count)
{
	t_token	**pipelines;

	pipelines = malloc(sizeof(t_token *) * (count + 1));
	return (pipelines);
}

static int	fill_pipelines(t_token **pipelines, t_token *tokens, int count)
{
	t_token	*current;
	int		i;

	current = tokens;
	i = 0;
	while (i < count && current)
	{
		pipelines[i] = copy_tokens_until_pipe(current, &current);
		if (!pipelines[i])
		{
			cleanup_pipelines(pipelines, i);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

t_token	**split_by_pipes(t_token *tokens, int *pipeline_count)
{
	t_token	**pipelines;
	int		count;

	if (!tokens || !pipeline_count)
		return (NULL);
	count = count_pipelines(tokens);
	*pipeline_count = count;
	pipelines = allocate_pipelines(count);
	if (!pipelines)
		return (NULL);
	if (fill_pipelines(pipelines, tokens, count) == FAILURE)
		return (NULL);
	pipelines[count] = NULL;
	return (pipelines);
}
