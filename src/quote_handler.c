/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:00:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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
