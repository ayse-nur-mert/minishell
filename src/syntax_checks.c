/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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

static int	check_consecutive_operators(char *input, int i)
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
			if (check_consecutive_operators(input, i) == FAILURE)
				return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}
