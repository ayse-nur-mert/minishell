/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 15:51:58 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static t_token	*extract_operator(const char *input, int *i)
{
	char	*content;
	
	if (input[*i] == '|')
	{
		content = ft_strdup("|");
		(*i)++;
		return (create_token_node(content, TOKEN_PIPE));
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			content = ft_strdup("<<");
			(*i) += 2;
			return (create_token_node(content, TOKEN_HEREDOC));
		}
		content = ft_strdup("<");
		(*i)++;
		return (create_token_node(content, TOKEN_REDIRECT_IN));
	}
	else if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			content = ft_strdup(">>");
			(*i) += 2;
			return (create_token_node(content, TOKEN_APPEND));
		}
		content = ft_strdup(">");
		(*i)++;
		return (create_token_node(content, TOKEN_REDIRECT_OUT));
	}
	return (NULL);
}


static t_token	*extract_word(const char *input, int *i)
{
	int		start;
	char	*content;
	t_token	*result;
	int		in_quote;
	char	quote_char;

	start = *i;
	in_quote = 0;
	quote_char = 0;
	while (input[*i])
	{
		if (is_quote(input[*i]) && (!in_quote || input[*i] == quote_char))
		{
			in_quote = !in_quote;
			if (in_quote)
				quote_char = input[*i];
			else
				quote_char = 0;
		}
		else if (!in_quote && is_token_separator(input[*i]))
			break ;
		(*i)++;
	}
	content = ft_substr(input, start, *i - start);
	if (!content)
		return (NULL);
	result = create_token_node(content, TOKEN_WORD);
	free(content);
	return (result);
}

t_token	*tokenize(char *input)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;
	
	tokens = NULL;
	i = 0;
	while (input && input[i])
	{
		skip_whitespace(input, &i);
		if (!input[i])
			break ;
		if (is_operator_char(input[i]))
		{
			new_token = extract_operator(input, &i);
			if (!new_token)
				return (NULL);
			add_token_node(&tokens, new_token);
		}
		else
		{
			new_token = extract_word(input, &i);
			if (!new_token)
				return (NULL);
			add_token_node(&tokens, new_token);
		}
	}
	return (tokens);
}

t_token	*tokenize_with_expansion(char *input, t_shell *shell)
{
	t_token	*tokens;
	t_token	*current;
	t_token	*next;
	t_token	*split_tokens;
	char	*expanded_content;
	char	**words;
	
	tokens = tokenize(input);
	if (!tokens || !shell)
		return (tokens);
	
	current = tokens;
	while (current)
	{
		next = current->next;
		if (current->type == TOKEN_WORD && ft_strchr(current->content, '$'))
		{
			expanded_content = expand_variables_in_string_quoted(current->content, shell);
			
			// Word splitting yap
			words = split_expanded_content(expanded_content);
			if (words && words[0])
			{
				// İlk token'ı güncelle
				free(current->content);
				current->content = ft_strdup(words[0]);
				
				// Eğer birden fazla kelime varsa, yeni token'lar oluştur
				if (words[1])
				{
					split_tokens = create_tokens_from_words(words + 1, TOKEN_WORD);
					if (split_tokens)
					{
						// Yeni token'ları mevcut token'dan sonra ekle
						t_token *last_new = split_tokens;
						while (last_new->next)
							last_new = last_new->next;
						
						last_new->next = current->next;
						if (current->next)
							current->next->prev = last_new;
						current->next = split_tokens;
						split_tokens->prev = current;
					}
				}
				free_word_array(words);
			}
			else
			{
				// Boş expansion - token'ı sil
				if (current->prev)
					current->prev->next = current->next;
				else
					tokens = current->next;
				if (current->next)
					current->next->prev = current->prev;
				free_token_node(current);
			}
			free(expanded_content);
		}
		current = next;
	}
	return (tokens);
}
