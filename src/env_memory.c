/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_memory.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 13:29:04 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	free_env_node(t_env *node)
{
	if (!node)
		return ;
	if (node->key)
		free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

void	free_env_list(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current)
	{
		next = current->next;
		free_env_node(current);
		current = next;
	}
}

int	count_env_nodes(t_env *env)
{
	int		count;
	t_env	*current;

	count = 0;
	current = env;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

static void	copy_env_to_array(t_env *env, char **array)
{
	t_env	*current;
	int		i;
	char	*temp;

	current = env;
	i = 0;
	while (current)
	{
		temp = ft_strjoin(current->key, "=");
		if (!temp)
			return ;
		array[i] = ft_strjoin(temp, current->value);
		free(temp);
		if (!array[i])
			return ;
		current = current->next;
		i++;
	}
	array[i] = NULL;
}

char	**env_to_array(t_env *env)
{
	char	**array;
	int		count;

	count = count_env_nodes(env);
	array = malloc(sizeof(char *) * (count + 1));
	if (!array)
		return (NULL);
	copy_env_to_array(env, array);
	return (array);
}
