/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_segments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

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
		if (input[i] == '|')
		{
			if (check_segment_content(i, segment_has_content) == FAILURE)
				return (FAILURE);
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
