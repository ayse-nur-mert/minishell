/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_operations.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 13:29:04 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

char	*get_env_value(t_env *env, char *key)
{
	t_env	*node;

	if (!env || !key)
		return (NULL);
	node = find_env_node(env, key);
	if (!node)
		return (NULL);
	return (node->value);
}

static int	update_existing_env(t_env *node, char *value)
{
	char	*new_value;

	new_value = ft_strdup(value);
	if (!new_value)
		return (FAILURE);
	free(node->value);
	node->value = new_value;
	return (SUCCESS);
}

int	set_env_value(t_env **env, char *key, char *value)
{
	t_env	*node;
	t_env	*new_node;

	if (!env || !key || !value)
		return (FAILURE);
	node = find_env_node(*env, key);
	if (node)
		return (update_existing_env(node, value));
	new_node = create_env_node(key, value);
	if (!new_node)
		return (FAILURE);
	add_env_node(env, new_node);
	return (SUCCESS);
}

int	unset_env_value(t_env **env, char *key)
{
	if (!env || !key)
		return (FAILURE);
	return (remove_env_node(env, key));
}

int	env_key_exists(t_env *env, char *key)
{
	if (!env || !key)
		return (0);
	if (find_env_node(env, key))
		return (1);
	return (0);
}
