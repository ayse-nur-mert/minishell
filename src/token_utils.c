/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 15:19:03 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_token	*create_token_node(char *content, e_token_types type)
{
	t_token	*new_token;
	char	*content_copy;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	if (content)
	{
		content_copy = ft_strdup(content);
		if (!content_copy)
		{
			free(new_token);
			return (NULL);
		}
		new_token->content = content_copy;
	}
	else
		new_token->content = NULL;
	new_token->type = type;
	new_token->prev = NULL;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_node(t_token **tokens, t_token *new_token)
{
	t_token	*current;

	if (!tokens || !new_token)
		return ;
	if (!*tokens)
	{
		*tokens = new_token;
		return ;
	}
	current = *tokens;
	while (current->next)
		current = current->next;
	current->next = new_token;
	new_token->prev = current;
}

t_token	*find_token_by_type(t_token *tokens, e_token_types type)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (current->type == type)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_token	*get_last_token(t_token *tokens)
{
	t_token	*current;

	if (!tokens)
		return (NULL);
	current = tokens;
	while (current->next)
		current = current->next;
	return (current);
}

int	remove_token_node(t_token **tokens, t_token *token_to_remove)
{
	if (!tokens || !*tokens || !token_to_remove)
		return (FAILURE);
	if (token_to_remove->prev)
		token_to_remove->prev->next = token_to_remove->next;
	else
		*tokens = token_to_remove->next;
	if (token_to_remove->next)
		token_to_remove->next->prev = token_to_remove->prev;
	if (token_to_remove->content)
		free(token_to_remove->content);
	free(token_to_remove);
	return (SUCCESS);
}
