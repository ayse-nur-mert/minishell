/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_helpers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/29 16:20:36 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	find_variable_end(const char *str, int start)
{
	int	i;

	if (!str || start < 0)
		return (start);
	i = start;
	if (str[i] == '?')
		return (i + 1);
	if (str[i] == '$')
		return (i + 1);
	if (str[i] >= '0' && str[i] <= '9')
		return (i + 1);
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (i);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

char	*extract_variable_name(const char *str, int start, int end)
{
	if (!str || start < 0 || end <= start)
		return (NULL);
	return (ft_substr(str, start, end - start));
}

char	*replace_in_string(const char *str, int start, int end,
	const char *replacement)
{
	char	*before;
	char	*after;
	char	*temp;
	char	*result;

	if (!str || !replacement || start < 0 || end < start)
		return (ft_strdup(str ? str : ""));
	before = ft_substr(str, 0, start);
	after = ft_strdup(str + end);
	if (!before || !after)
	{
		if (before)
			free(before);
		if (after)
			free(after);
		return (ft_strdup(str));
	}
	temp = ft_strjoin(before, replacement);
	result = ft_strjoin(temp, after);
	free(before);
	free(after);
	free(temp);
	return (result ? result : ft_strdup(""));
}
