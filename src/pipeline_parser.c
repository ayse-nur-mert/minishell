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

static int	count_pipelines(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 1;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
			count++;
		current = current->next;
	}
	return (count);
}

static t_token	*copy_tokens_until_pipe(t_token *start, t_token **next_start)
{
	t_token	*new_list;
	t_token	*current;
	t_token	*new_token;

	new_list = NULL;
	current = start;
	while (current && current->type != TOKEN_PIPE)
	{
		new_token = create_token_node(current->content, current->type);
		if (!new_token)
		{
			free_tokens(new_list);
			return (NULL);
		}
		add_token_node(&new_list, new_token);
		current = current->next;
	}
	if (current && current->type == TOKEN_PIPE)
		*next_start = current->next;
	else
		*next_start = NULL;
	return (new_list);
}

t_token	**split_by_pipes(t_token *tokens, int *pipeline_count)
{
	t_token	**pipelines;
	t_token	*current;
	int		count;
	int		i;

	if (!tokens || !pipeline_count)
		return (NULL);
	count = count_pipelines(tokens);
	*pipeline_count = count;
	pipelines = malloc(sizeof(t_token *) * (count + 1));
	if (!pipelines)
		return (NULL);
	current = tokens;
	i = 0;
	while (i < count && current)
	{
		pipelines[i] = copy_tokens_until_pipe(current, &current);
		if (!pipelines[i])
		{
			while (--i >= 0)
				free_tokens(pipelines[i]);
			free(pipelines);
			return (NULL);
		}
		i++;
	}
	pipelines[count] = NULL;
	return (pipelines);
}

void	free_pipeline_array(t_token **pipelines)
{
	int	i;

	if (!pipelines)
		return ;
	i = 0;
	while (pipelines[i])
	{
		free_tokens(pipelines[i]);
		i++;
	}
	free(pipelines);
}
