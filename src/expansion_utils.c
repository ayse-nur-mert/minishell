/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 15:32:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

/**
 * Handles special shell variables like $?, $$, $0
 * @param name The name of the variable without $
 * @param shell The shell structure containing exit_status
 * @return Expanded value of special variable or NULL if not special
 * Note: Caller must free the returned string
 */
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

/**
 * Expands a variable
 * @param var Variable name without the $
 * @param shell Shell structure for env and special vars
 * @return Expanded variable value or empty string if not found
 * Note: Caller must free the returned string
 */
char	*expand_variable(char *var, t_shell *shell)
{
	char	*value;

	if (!var || !shell)
		return (ft_strdup(""));
	
	/* First check for special vars */
	value = handle_special_vars(var, shell);
	if (value)
		return (value);
	
	/* Then check environment */
	value = get_env_value(shell->env, var);
	if (value)
		return (ft_strdup(value));
	
	/* Variable not found */
	return (ft_strdup(""));
}
