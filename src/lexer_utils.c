/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 15:51:31 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_token_separator(char c)
{
	return (is_whitespace(c) || is_operator_char(c));
}


int	skip_whitespace(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && is_whitespace(str[*i]))
		(*i)++;
	return (*i > start);
}

int	is_token_char(char c)
{
	return (c && !is_whitespace(c) && !is_operator_char(c));
}
