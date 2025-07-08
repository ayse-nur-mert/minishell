/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/08 15:51:31 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

static int	check_operator_at_end(char *input)
{
	int	len;
	int	i;

	len = ft_strlen(input);
	i = len - 1;
	while (i >= 0 && (input[i] == ' ' || input[i] == '\t'))
		i--;
	if (i >= 0 && is_operator_char(input[i]))
	{
		if (!(input[i] == '>' && i > 0 && input[i - 1] == '>'))
		{
			print_syntax_error("operator at end of input", i);
			return (FAILURE);
		}
	}
	return (SUCCESS);
}

static int	check_operator_at_start(char *input)
{
	int	i;

	i = 0;
	while (input[i] && (input[i] == ' ' || input[i] == '\t'))
		i++;
	if (input[i] && input[i] == '|')
	{
		print_syntax_error("pipe at beginning of input", i);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	check_operator_syntax(char *input)
{
	int	i;

	if (check_operator_at_start(input) == FAILURE)
		return (FAILURE);
	if (check_operator_at_end(input) == FAILURE)
		return (FAILURE);
	i = 0;
	while (input[i])
	{
		if (is_operator_char(input[i]))
		{
			if (input[i] == '|' && input[i + 1] == '|')
			{
				print_syntax_error("consecutive pipes", i);
				return (FAILURE);
			}
			if (input[i] == '>' && input[i + 1] == '<')
			{
				print_syntax_error("invalid redirect sequence", i);
				return (FAILURE);
			}
			if (input[i] == '<' && input[i + 1] == '>')
			{
				print_syntax_error("invalid redirect sequence", i);
				return (FAILURE);
			}
		}
		i++;
	}
	return (SUCCESS);
}

int	check_empty_segments(char *input)
{
	int	i;
	int	segment_has_content;

	i = 0;
	segment_has_content = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (!segment_has_content)
			{
				print_syntax_error("empty command before pipe", i);
				return (FAILURE);
			}
			segment_has_content = 0;
		}
		else if (input[i] != ' ' && input[i] != '\t')
			segment_has_content = 1;
		i++;
	}
	if (input[i - 1] == '|' && !segment_has_content)
	{
		print_syntax_error("empty command after pipe", i - 1);
		return (FAILURE);
	}
	return (SUCCESS);
}

int	validate_syntax(char *input)
{
	if (!input || !*input)
		return (SUCCESS);
	if (check_quote_matching(input) == FAILURE)
		return (FAILURE);
	if (check_operator_syntax(input) == FAILURE)
		return (FAILURE);
	if (check_empty_segments(input) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}
