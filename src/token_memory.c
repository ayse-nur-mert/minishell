/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 15:19:03 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_token_node(t_token *token)
{
	if (!token)
		return ;
	if (token->content)
		free(token->content);
	free(token);
}

void	free_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*next;

	current = tokens;
	while (current)
	{
		next = current->next;
		free_token_node(current);
		current = next;
	}
}

int	count_tokens(t_token *tokens)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

int	count_tokens_by_type(t_token *tokens, e_token_types type)
{
	int		count;
	t_token	*current;

	count = 0;
	current = tokens;
	while (current)
	{
		if (current->type == type)
			count++;
		current = current->next;
	}
	return (count);
}

t_token	*duplicate_token_list(t_token *tokens)
{
	t_token	*new_list;
	t_token	*current;
	t_token	*new_token;

	new_list = NULL;
	current = tokens;
	while (current)
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
	return (new_list);
}
