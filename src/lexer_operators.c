/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_operators.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static t_token	*handle_pipe_operator(int *i)
{
	char	*content;

	content = ft_strdup("|");
	(*i)++;
	return (create_token_node(content, TOKEN_PIPE));
}

static t_token	*handle_input_redirect(const char *input, int *i)
{
	char	*content;

	if (input[*i + 1] == '<')
	{
		content = ft_strdup("<<");
		(*i) += 2;
		return (create_token_node(content, TOKEN_HEREDOC));
	}
	content = ft_strdup("<");
	(*i)++;
	return (create_token_node(content, TOKEN_REDIRECT_IN));
}

static t_token	*handle_output_redirect(const char *input, int *i)
{
	char	*content;

	if (input[*i + 1] == '>')
	{
		content = ft_strdup(">>");
		(*i) += 2;
		return (create_token_node(content, TOKEN_APPEND));
	}
	content = ft_strdup(">");
	(*i)++;
	return (create_token_node(content, TOKEN_REDIRECT_OUT));
}

t_token	*extract_operator(const char *input, int *i)
{
	if (input[*i] == '|')
		return (handle_pipe_operator(i));
	else if (input[*i] == '<')
		return (handle_input_redirect(input, i));
	else if (input[*i] == '>')
		return (handle_output_redirect(input, i));
	return (NULL);
}
