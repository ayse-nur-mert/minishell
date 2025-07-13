/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	**split_expanded_content(char *content)
{
	char	**words;
	char	*trimmed;

	if (!content)
		return (NULL);
	trimmed = ft_strtrim(content, " \t\n");
	if (!trimmed || *trimmed == '\0')
	{
		if (trimmed)
			free(trimmed);
		return (NULL);
	}
	words = ft_split(trimmed, ' ');
	free(trimmed);
	return (words);
}

t_token	*create_tokens_from_words(char **words, t_token_types type)
{
	t_token	*tokens;
	t_token	*new_token;
	int		i;

	if (!words)
		return (NULL);
	tokens = NULL;
	i = 0;
	while (words[i])
	{
		new_token = create_token_node(words[i], type);
		if (!new_token)
		{
			free_tokens(tokens);
			return (NULL);
		}
		add_token_node(&tokens, new_token);
		i++;
	}
	return (tokens);
}

void	free_word_array(char **words)
{
	int	i;

	if (!words)
		return ;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}
