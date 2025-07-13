/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_classifier.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:05:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 14:05:00 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	classify_word_token(t_token *token, t_token *prev_token)
{
	if (!prev_token)
	{
		token->type = TOKEN_COMMAND;
		return ;
	}
	if (prev_token->type == TOKEN_REDIRECT_IN || 
		prev_token->type == TOKEN_REDIRECT_OUT ||
		prev_token->type == TOKEN_APPEND || 
		prev_token->type == TOKEN_HEREDOC)
	{
		token->type = TOKEN_FILE;
		return ;
	}
	if (prev_token->type == TOKEN_PIPE)
	{
		token->type = TOKEN_COMMAND;
		return ;
	}
	if (prev_token->type == TOKEN_COMMAND || 
		prev_token->type == TOKEN_ARGUMENT)
	{
		token->type = TOKEN_ARGUMENT;
		return ;
	}
	token->type = TOKEN_ARGUMENT;
}

void	classify_tokens(t_token *tokens)
{
	t_token	*current;
	t_token	*prev_word;

	current = tokens;
	prev_word = NULL;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			classify_word_token(current, prev_word);
			prev_word = current;
		}
		else if (current->type == TOKEN_PIPE)
		{
			prev_word = current;
		}
		else if (is_redirect_token(current->type))
		{
			prev_word = current;
		}
		current = current->next;
	}
}
