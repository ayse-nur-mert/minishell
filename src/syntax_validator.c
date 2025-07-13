/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_validator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:50:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 13:46:13 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/minishell.h"

void	print_syntax_error(char *error_msg, int position)
{
	printf("minishell: syntax error");
	if (error_msg)
		printf(": %s", error_msg);
	if (position >= 0)
		printf(" at position %d", position);
	printf("\n");
}

int	check_quote_matching(char *input)
{
	int		i;
	int		in_single_quote;
	int		in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (input[i])
	{
		if (input[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (input[i] == '"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	if (in_single_quote)
		return (print_syntax_error("unclosed single quote", -1), FAILURE);
	if (in_double_quote)
		return (print_syntax_error("unclosed double quote", -1), FAILURE);
	return (SUCCESS);
}
