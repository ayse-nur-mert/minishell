/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

int	is_operator_char(char c)
{
	return (c == '|' || c == '<' || c == '>');
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
