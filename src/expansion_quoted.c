/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_quoted.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:40:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	is_escaped(const char *str, int pos)
{
	int	count;

	count = 0;
	pos--;
	while (pos >= 0 && str[pos] == '\\')
	{
		count++;
		pos--;
	}
	return (count % 2 == 1);
}

static int	should_expand_at_position(const char *str, int pos)
{
	int	i;
	int	in_single;
	int	in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos && str[i])
	{
		if (str[i] == '\'' && !is_escaped(str, i) && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !is_escaped(str, i) && !in_single)
			in_double = !in_double;
		i++;
	}
	if (in_single)
		return (0);
	return (1);
}

static char	*process_quoted_expansion(char *result, int i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;
	int		var_end;

	var_end = find_variable_end(result, i + 1);
	if (var_end <= i + 1)
		return (result);
	var_name = extract_variable_name(result, i + 1, var_end);
	var_value = expand_variable(var_name, shell);
	new_result = replace_in_string(result, i, var_end, var_value);
	free(var_name);
	free(var_value);
	return (new_result);
}

char	*expand_variables_in_string_quoted(char *str, t_shell *shell)
{
	char	*result;
	char	*new_result;
	char	*var_value;
	int		i;

	if (!str || !shell)
		return (ft_strdup(""));
	result = ft_strdup(str);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1]
			&& should_expand_at_position(result, i) && !is_escaped(result, i))
		{
			new_result = process_quoted_expansion(result, i, shell);
			free(result);
			result = new_result;
			var_value = expand_variable("", shell);
			i += ft_strlen(var_value);
			free(var_value);
			continue ;
		}
		i++;
	}
	return (result);
}
