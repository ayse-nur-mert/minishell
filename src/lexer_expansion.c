/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	insert_split_tokens(t_token *current, t_token *split_tokens)
{
	t_token	*last_new;

	last_new = split_tokens;
	while (last_new->next)
		last_new = last_new->next;
	last_new->next = current->next;
	if (current->next)
		current->next->prev = last_new;
	current->next = split_tokens;
	split_tokens->prev = current;
}

static void	remove_empty_token(t_token **tokens, t_token *current)
{
	if (current->prev)
		current->prev->next = current->next;
	else
		*tokens = current->next;
	if (current->next)
		current->next->prev = current->prev;
	free_token_node(current);
}

static void	process_word_expansion(t_token **tokens, t_token *current,
									t_shell *shell)
{
	char	*expanded_content;
	char	**words;
	t_token	*split_tokens;

	expanded_content = expand_variables_in_string_quoted(current->content,
			shell);
	words = split_expanded_content(expanded_content);
	if (words && words[0])
	{
		free(current->content);
		current->content = ft_strdup(words[0]);
		if (words[1])
		{
			split_tokens = create_tokens_from_words(words + 1, TOKEN_WORD);
			if (split_tokens)
				insert_split_tokens(current, split_tokens);
		}
		free_word_array(words);
	}
	else
		remove_empty_token(tokens, current);
	free(expanded_content);
}

t_token	*tokenize_with_expansion(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_token	*current;
	t_token	*next;

	tokens = tokenize(input);
	if (!tokens || !shell)
		return (tokens);
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD && ft_strchr(current->content, '$'))
		{
			// Heredoc delimiter kontrolü
			if (current->prev && current->prev->type == TOKEN_HEREDOC)
			{
				// Heredoc delimiter - genişletme yapma
				current = next;
				continue;
			}
			process_word_expansion(&tokens, current, shell);
		}
		current = next;
	}
	return (tokens);
}
