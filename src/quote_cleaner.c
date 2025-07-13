/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_cleaner.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static void	handle_quote_toggle(char c, int *in_quote, char *quote_char)
{
	if (!*in_quote)
	{
		*quote_char = c;
		*in_quote = 1;
	}
	else
	{
		*in_quote = 0;
		*quote_char = 0;
	}
}

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
			handle_quote_toggle(str[i], &in_quote, &quote_char);
		else
			result[j++] = str[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}
