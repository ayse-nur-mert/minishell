/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	count_pipelines(t_token *tokens)
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

void	cleanup_pipelines(t_token **pipelines, int count)
{
	while (--count >= 0)
		free_tokens(pipelines[count]);
	free(pipelines);
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
