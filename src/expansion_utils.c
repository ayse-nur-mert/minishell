/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 13:33:42 by amert            ###   ########.fr       */
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

static int	find_variable_end(const char *str, int start)
{
	int	i;

	i = start;
	// Özel değişkenler: $?, $$, $0
	if (str[i] == '?')
		return (i + 1);
	if (str[i] == '$')
		return (i + 1);
	if (str[i] >= '0' && str[i] <= '9')
		return (i + 1);
	// Normal değişken ismi kontrolleri
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (i);
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}

static char	*extract_variable_name(const char *str, int start, int end)
{
	return (ft_substr(str, start, end - start));
}

static char	*replace_in_string(const char *str, int start, int end, const char *replacement)
{
	char	*before;
	char	*after;
	char	*temp;
	char	*result;

	before = ft_substr(str, 0, start);
	after = ft_strdup(str + end);
	temp = ft_strjoin(before, replacement);
	result = ft_strjoin(temp, after);
	free(before);
	free(after);
	free(temp);
	return (result);
}

char	*expand_variables_in_string(char *str, t_shell *shell)
{
	char	*result;
	char	*new_result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		var_end;

	if (!str || !shell)
		return (ft_strdup(""));
	result = ft_strdup(str);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1])
		{
			var_end = find_variable_end(result, i + 1);
			if (var_end > i + 1)
			{
				var_name = extract_variable_name(result, i + 1, var_end);
				var_value = expand_variable(var_name, shell);
				new_result = replace_in_string(result, i, var_end, var_value);
				free(result);
				result = new_result;
				i += ft_strlen(var_value);
				free(var_name);
				free(var_value);
				continue;
			}
		}
		i++;
	}
	return (result);
}

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
	// Single quote içinde genişletme yapma, double quote içinde yap
	if (in_single)
		return (0);
	return (1);
}

char	*expand_variables_in_string_quoted(char *str, t_shell *shell)
{
	char	*result;
	char	*new_result;
	char	*var_name;
	char	*var_value;
	int		i;
	int		var_end;

	if (!str || !shell)
		return (ft_strdup(""));
	result = ft_strdup(str);
	i = 0;
	while (result[i])
	{
		if (result[i] == '$' && result[i + 1] && should_expand_at_position(result, i) && !is_escaped(result, i))
		{
			var_end = find_variable_end(result, i + 1);
			if (var_end > i + 1)
			{
				var_name = extract_variable_name(result, i + 1, var_end);
				var_value = expand_variable(var_name, shell);
				new_result = replace_in_string(result, i, var_end, var_value);
				free(result);
				result = new_result;
				i += ft_strlen(var_value);
				free(var_name);
				free(var_value);
				continue;
			}
		}
		i++;
	}
	return (result);
}

char	**split_expanded_content(char *content)
{
	char	**words;
	char	*trimmed;
	
	if (!content)
		return (NULL);
	
	// Başta ve sonda boşlukları temizle
	trimmed = ft_strtrim(content, " \t\n");
	if (!trimmed || *trimmed == '\0')
	{
		if (trimmed)
			free(trimmed);
		return (NULL);
	}
	
	// Boşluklara göre böl
	words = ft_split(trimmed, ' ');
	free(trimmed);
	return (words);
}

t_token	*create_tokens_from_words(char **words, e_token_types type)
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
		return;
	i = 0;
	while (words[i])
	{
		free(words[i]);
		i++;
	}
	free(words);
}
