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
