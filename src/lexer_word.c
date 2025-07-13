/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	handle_quote_char(const char *input, int *i, int *in_quote,
							char *quote_char)
{
	if (is_quote(input[*i]) && (!*in_quote || input[*i] == *quote_char))
	{
		*in_quote = !*in_quote;
		if (*in_quote)
			*quote_char = input[*i];
		else
			*quote_char = 0;
	}
}

t_token	*extract_word(const char *input, int *i)
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
		handle_quote_char(input, i, &in_quote, &quote_char);
		if (!in_quote && is_token_separator(input[*i]))
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
