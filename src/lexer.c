/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static t_token	*process_token(char *input, int *i)
{
	t_token	*new_token;

	if (is_operator_char(input[*i]))
	{
		new_token = extract_operator(input, i);
		if (!new_token)
			return (NULL);
		return (new_token);
	}
	else
	{
		new_token = extract_word(input, i);
		if (!new_token)
			return (NULL);
		return (new_token);
	}
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
		new_token = process_token(input, &i);
		if (!new_token)
			return (NULL);
		add_token_node(&tokens, new_token);
	}
	return (tokens);
}
