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

/* Removed duplicate definition of is_operator_char - now using the one from header */

int	is_token_separator(char c)
{
	return (is_whitespace(c) || is_operator_char(c));
}

/**
 * Skip whitespace characters in a string
 * @param str The string to process
 * @param i Pointer to current position
 * @return 1 if whitespace was skipped, 0 otherwise
 */
int	skip_whitespace(const char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] && is_whitespace(str[*i]))
		(*i)++;
	return (*i > start);
}

/**
 * Determines if a character is part of a token
 * @param c Character to check
 * @return 1 if part of a token, 0 otherwise
 */
int	is_token_char(char c)
{
	return (c && !is_whitespace(c) && !is_operator_char(c));
}
