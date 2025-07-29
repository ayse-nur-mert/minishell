/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_segments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/29 16:20:36 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

static int	is_in_quotes(char *input, int pos)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (i <= pos && input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote || in_double_quote);
}

static int	check_segment_content(int i, int segment_has_content)
{
	if (!segment_has_content)
	{
		print_syntax_error("empty command before pipe", i);
		return (FAILURE);
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
		if (input[i] == '|' && !is_in_quotes(input, i))
		{
			if (check_segment_content(i, segment_has_content) == FAILURE)
				return (FAILURE);
			segment_has_content = 0;
		}
		else if (input[i] != ' ' && input[i] != '\t')
			segment_has_content = 1;
		i++;
	}
	if (i > 0 && input[i - 1] == '|' && !is_in_quotes(input, i - 1) && !segment_has_content)
	{
		print_syntax_error("empty command after pipe", i - 1);
		return (FAILURE);
	}
	return (SUCCESS);
}
