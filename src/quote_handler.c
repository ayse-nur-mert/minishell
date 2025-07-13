/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:00:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 14:25:30 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*remove_quotes(const char *str)
{
	char	*result;
	int		i;
	int		j;
	int		in_quote;
	char	quote_char;

	if (!str)
		return (NULL);
	result = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	in_quote = 0;
	quote_char = 0;
	while (str[i])
	{
		if (is_quote(str[i]) && (!in_quote || str[i] == quote_char))
		{
			if (!in_quote)
			{
				quote_char = str[i];
				in_quote = 1;
			}
			else
			{
				in_quote = 0;
				quote_char = 0;
			}
		}
		else
		{
			result[j++] = str[i];
		}
		i++;
	}
	result[j] = '\0';
	return (result);
}

void	clean_token_quotes(t_token *tokens)
{
	t_token	*current;
	char	*cleaned;

	current = tokens;
	while (current)
	{
		if (current->type == TOKEN_WORD)
		{
			cleaned = remove_quotes(current->content);
			if (cleaned)
			{
				free(current->content);
				current->content = cleaned;
			}
		}
		current = current->next;
	}
}
