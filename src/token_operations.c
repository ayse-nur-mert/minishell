/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_redirect_token(t_token_types type)
{
	return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT
		|| type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

int	is_operator_token(t_token_types type)
{
	return (type == TOKEN_PIPE || is_redirect_token(type));
}

t_token	*get_next_word_token(t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token->next;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			return (current);
		current = current->next;
	}
	return (NULL);
}

t_token	*get_prev_word_token(t_token *token)
{
	t_token	*current;

	if (!token)
		return (NULL);
	current = token->prev;
	while (current)
	{
		if (current->type == TOKEN_WORD)
			return (current);
		current = current->prev;
	}
	return (NULL);
}

int	validate_token_sequence(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (is_operator_token(current->type))
		{
			if (!current->next)
				return (FAILURE);
			if (current->type == TOKEN_PIPE
				&& (!current->prev || current->prev->type != TOKEN_WORD))
				return (FAILURE);
		}
		current = current->next;
	}
	return (SUCCESS);
}
