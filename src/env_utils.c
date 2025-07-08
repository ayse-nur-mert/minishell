/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 13:52:00 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;
	char	*key_copy;
	char	*value_copy;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	key_copy = ft_strdup(key);
	if (!key_copy)
	{
		free(new_node);
		return (NULL);
	}
	value_copy = ft_strdup(value);
	if (!value_copy)
	{
		free(key_copy);
		free(new_node);
		return (NULL);
	}
	new_node->key = key_copy;
	new_node->value = value_copy;
	new_node->next = NULL;
	return (new_node);
}

void	add_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_env	*find_env_node(t_env *env, char *key)
{
	t_env	*current;

	if (!env || !key)
		return (NULL);
	current = env;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0
			&& ft_strlen(current->key) == ft_strlen(key))
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	remove_env_node(t_env **env, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env || !*env || !key)
		return (FAILURE);
	current = *env;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0
			&& ft_strlen(current->key) == ft_strlen(key))
		{
			if (prev)
				prev->next = current->next;
			else
				*env = current->next;
			free(current->key);
			free(current->value);
			free(current);
			return (SUCCESS);
		}
		prev = current;
		current = current->next;
	}
	return (FAILURE);
}
