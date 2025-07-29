/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_core.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:35:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/29 16:23:43 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*handle_special_vars(char *name, t_shell *shell)
{
	if (!name || !shell)
		return (NULL);
	if (ft_strncmp(name, "?", 2) == 0)
		return (ft_itoa(shell->exit_status));
	if (ft_strncmp(name, "$", 2) == 0)
		return (ft_itoa(getpid()));
	if (ft_strncmp(name, "0", 2) == 0)
		return (ft_strdup("minishell"));
	return (NULL);
}

char	*expand_variable(char *var, t_shell *shell)
{
	char	*value;

	if (!var || !shell)
		return (ft_strdup(""));
	value = handle_special_vars(var, shell);
	if (value)
		return (value);
	value = get_env_value(shell->env, var);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

static void	process_variable_expansion(char **result, int *i, t_shell *shell)
{
	char	*var_name;
	char	*var_value;
	int		var_end;

	var_end = find_variable_end(*result, *i + 1);
	if (var_end > *i + 1)
	{
		var_name = extract_variable_name(*result, *i + 1, var_end);
		if (var_name)
		{
			var_value = expand_variable(var_name, shell);
			*result = replace_in_string(*result, *i, var_end, var_value ? var_value : "");
			if (var_value)
			{
				*i += ft_strlen(var_value);
				free(var_value);
			}
			free(var_name);
		}
		else
			(*i)++;
	}
	else
		(*i)++;
}

char	*expand_variables_in_string(char *str, t_shell *shell)
{
	char	*result;
	char	*old_result;
	int		i;

	if (!str || !shell)
		return (ft_strdup(""));
	result = ft_strdup(str);
	if (!result)
		return (ft_strdup(""));
	i = 0;
	while (result && result[i])
	{
		if (result[i] == '$' && result[i + 1])
		{
			old_result = result;
			process_variable_expansion(&result, &i, shell);
			if (result != old_result)
				free(old_result);
		}
		else
			i++;
	}
	return (result);
}
