/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 14:38:45 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static char	*find_equal_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (&str[i]);
		i++;
	}
	return (NULL);
}

static int	extract_key_value(char *env_var, char **key, char **value)
{
	char	*equal_pos;
	int		key_len;

	equal_pos = find_equal_sign(env_var);
	if (!equal_pos)
		return (FAILURE);
	key_len = equal_pos - env_var;
	*key = ft_substr(env_var, 0, key_len);
	if (!*key)
		return (FAILURE);
	*value = ft_strdup(equal_pos + 1);
	if (!*value)
	{
		free(*key);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	add_env_variable(t_env **env, char *env_var)
{
	char	*key;
	char	*value;
	t_env	*new_node;

	if (extract_key_value(env_var, &key, &value) == FAILURE)
		return (FAILURE);
	new_node = create_env_node(key, value);
	free(key);
	free(value);
	if (!new_node)
		return (FAILURE);
	add_env_node(env, new_node);
	return (SUCCESS);
}

t_env	*init_env_from_system(char **environ)
{
	t_env	*env;
	int		i;

	env = NULL;
	if (!environ)
		return (NULL);
	i = 0;
	while (environ[i])
	{
		if (add_env_variable(&env, environ[i]) == FAILURE)
		{
			free_env_list(env);
			return (NULL);
		}
		i++;
	}
	return (env);
}
