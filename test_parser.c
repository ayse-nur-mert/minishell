/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amert <amert@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:00:00 by amert             #+#    #+#             */
/*   Updated: 2025/07/13 16:07:24 by amert            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/minishell.h"

void	print_token_details(t_token *token)
{
	const char	*type_names[] = {
		"TOKEN_NONE", "TOKEN_WORD", "TOKEN_COMMAND", "TOKEN_ARGUMENT",
		"TOKEN_FILE", "TOKEN_PIPE", "TOKEN_REDIRECT_IN", "TOKEN_REDIRECT_OUT",
		"TOKEN_APPEND", "TOKEN_HEREDOC"
	};

	if (!token)
	{
		printf("NULL token\n");
		return ;
	}
	printf("Token: '%s' | Type: %s\n", 
		token->content ? token->content : "NULL", 
		type_names[token->type]);
}

void	print_all_tokens(t_token *tokens)
{
	t_token	*current;
	int		count;

	current = tokens;
	count = 0;
	printf("\n=== ALL TOKENS ===\n");
	while (current)
	{
		printf("[%d] ", count++);
		print_token_details(current);
		current = current->next;
	}
	printf("Total tokens: %d\n\n", count);
}

void	print_pipelines(t_token **pipelines, int pipeline_count)
{
	int		i;
	t_token	*current;
	int		token_count;

	printf("=== PIPELINES (%d) ===\n", pipeline_count);
	i = 0;
	while (i < pipeline_count)
	{
		printf("Pipeline %d:\n", i);
		current = pipelines[i];
		token_count = 0;
		while (current)
		{
			printf("  [%d] ", token_count++);
			print_token_details(current);
			current = current->next;
		}
		printf("  Tokens in pipeline: %d\n\n", token_count);
		i++;
	}
}

void	test_basic_tokenization(void)
{
	char	*test_cases[] = {
		"echo hello world",
		"ls -la",
		"cat file.txt",
		"grep pattern file",
		"echo 'hello world'",
		"echo \"hello world\"",
		"echo hello > output.txt",
		"cat < input.txt",
		"ls >> log.txt",
		"cat << EOF",
		"echo hello | grep h",
		"ls | grep .txt | wc -l",
		"echo $USER",
		"echo $HOME/Desktop",
		"echo \"$USER is here\"",
		"echo '$USER'",
		"",
		"   ",
		NULL
	};
	t_token	*tokens;
	int		i;

	printf("\n" "========================================\n");
	printf("BASIC TOKENIZATION TESTS\n");
	printf("========================================\n");
	
	i = 0;
	while (test_cases[i])
	{
		printf("\nTest case %d: \"%s\"\n", i + 1, test_cases[i]);
		printf("----------------------------------------\n");
		
		tokens = tokenize(test_cases[i]);
		if (tokens)
		{
			print_all_tokens(tokens);
			free_tokens(tokens);
		}
		else
		{
			printf("Tokenization failed or returned NULL\n");
		}
		i++;
	}
}

void	test_syntax_validation(void)
{
	char	*valid_cases[] = {
		"echo hello",
		"ls | grep test",
		"cat file > output",
		"echo \"hello world\"",
		"echo 'single quotes'",
		"cat << EOF",
		"ls >> log.txt",
		"cat < input | grep pattern",
		NULL
	};
	
	char	*invalid_cases[] = {
		"|",
		"echo |",
		"| echo",
		"echo hello |",
		"echo | | ls",
		"echo \"unclosed",
		"echo 'unclosed",
		"echo > < file",
		"echo < > file",
		"",
		"   ",
		NULL
	};
	
	int		i;
	int		result;

	printf("\n" "========================================\n");
	printf("SYNTAX VALIDATION TESTS\n");
	printf("========================================\n");
	
	printf("\n--- VALID CASES ---\n");
	i = 0;
	while (valid_cases[i])
	{
		printf("Test %d: \"%s\" -> ", i + 1, valid_cases[i]);
		result = validate_syntax(valid_cases[i]);
		printf("%s\n", result == SUCCESS ? "✓ VALID" : "✗ INVALID");
		i++;
	}
	
	printf("\n--- INVALID CASES ---\n");
	i = 0;
	while (invalid_cases[i])
	{
		printf("Test %d: \"%s\" -> ", i + 1, invalid_cases[i]);
		result = validate_syntax(invalid_cases[i]);
		printf("%s\n", result == FAILURE ? "✓ CORRECTLY REJECTED" : "✗ INCORRECTLY ACCEPTED");
		i++;
	}
}

void	test_pipeline_parsing(void)
{
	char	*test_cases[] = {
		"echo hello",
		"echo hello | grep h",
		"ls | grep .txt | wc -l",
		"cat file | sort | uniq | head -10",
		"echo test | cat | cat | cat",
		NULL
	};
	
	t_token		*tokens;
	t_token		**pipelines;
	int			pipeline_count;
	int			i;

	printf("\n" "========================================\n");
	printf("PIPELINE PARSING TESTS\n");
	printf("========================================\n");
	
	i = 0;
	while (test_cases[i])
	{
		printf("\nTest case %d: \"%s\"\n", i + 1, test_cases[i]);
		printf("----------------------------------------\n");
		
		tokens = tokenize(test_cases[i]);
		if (tokens)
		{
			classify_tokens(tokens);
			pipelines = split_by_pipes(tokens, &pipeline_count);
			if (pipelines)
			{
				print_pipelines(pipelines, pipeline_count);
				free_pipeline_array(pipelines);
			}
			else
			{
				printf("Pipeline parsing failed\n");
			}
			free_tokens(tokens);
		}
		else
		{
			printf("Tokenization failed\n");
		}
		i++;
	}
}

void	test_token_classification(void)
{
	char	*test_cases[] = {
		"echo hello world",
		"ls -la /home",
		"cat file.txt > output.txt",
		"grep pattern < input.txt",
		"ls | grep test",
		"echo hello >> log.txt",
		"cat << EOF",
		NULL
	};
	
	t_token	*tokens;
	int		i;

	printf("\n" "========================================\n");
	printf("TOKEN CLASSIFICATION TESTS\n");
	printf("========================================\n");
	
	i = 0;
	while (test_cases[i])
	{
		printf("\nTest case %d: \"%s\"\n", i + 1, test_cases[i]);
		printf("----------------------------------------\n");
		
		tokens = tokenize(test_cases[i]);
		if (tokens)
		{
			printf("Before classification:\n");
			print_all_tokens(tokens);
			
			classify_tokens(tokens);
			
			printf("After classification:\n");
			print_all_tokens(tokens);
			
			free_tokens(tokens);
		}
		else
		{
			printf("Tokenization failed\n");
		}
		i++;
	}
}

void	test_quote_handling(void)
{
	char	*test_cases[] = {
		"echo \"hello world\"",
		"echo 'single quotes'",
		"echo \"mixed 'quotes'\"",
		"echo 'mixed \"quotes\"'",
		"echo \"$USER is here\"",
		"echo '$USER is here'",
		"echo \"file with spaces.txt\"",
		"echo 'don\\'t'",
		"echo \"can\\'t\"",
		NULL
	};
	
	t_token	*tokens;
	int		i;

	printf("\n" "========================================\n");
	printf("QUOTE HANDLING TESTS\n");
	printf("========================================\n");
	
	i = 0;
	while (test_cases[i])
	{
		printf("\nTest case %d: \"%s\"\n", i + 1, test_cases[i]);
		printf("----------------------------------------\n");
		
		tokens = tokenize(test_cases[i]);
		if (tokens)
		{
			printf("Before quote cleaning:\n");
			print_all_tokens(tokens);
			
			clean_token_quotes(tokens);
			
			printf("After quote cleaning:\n");
			print_all_tokens(tokens);
			
			free_tokens(tokens);
		}
		else
		{
			printf("Tokenization failed\n");
		}
		i++;
	}
}

void	test_variable_expansion(void)
{
	t_shell	shell;
	char	*test_cases[] = {
		"echo $USER",
		"echo $HOME",
		"echo $PATH",
		"echo $?",
		"echo $$",
		"echo $0",
		"echo $NONEXISTENT",
		"echo \"$USER is here\"",
		"echo '$USER is here'",
		"echo $USER$HOME",
		NULL
	};
	
	t_token	*tokens;
	int		i;

	printf("\n" "========================================\n");
	printf("VARIABLE EXPANSION TESTS\n");
	printf("========================================\n");
	
	// Initialize shell with basic environment
	shell.env = NULL;
	shell.exit_status = 42;
	set_env_value(&shell.env, "USER", "testuser");
	set_env_value(&shell.env, "HOME", "/home/testuser");
	set_env_value(&shell.env, "PATH", "/bin:/usr/bin");
	
	i = 0;
	while (test_cases[i])
	{
		printf("\nTest case %d: \"%s\"\n", i + 1, test_cases[i]);
		printf("----------------------------------------\n");
		
		tokens = tokenize_with_expansion(test_cases[i], &shell);
		if (tokens)
		{
			print_all_tokens(tokens);
			free_tokens(tokens);
		}
		else
		{
			printf("Tokenization with expansion failed\n");
		}
		i++;
	}
	
	free_env_list(shell.env);
}

int	main(void)
{
	printf("MINISHELL PARSER COMPREHENSIVE TEST SUITE\n");
	printf("==========================================\n");
	
	test_basic_tokenization();
	test_syntax_validation();
	test_token_classification();
	test_pipeline_parsing();
	test_quote_handling();
	test_variable_expansion();
	
	printf("\n" "========================================\n");
	printf("ALL TESTS COMPLETED\n");
	printf("========================================\n");
	
	return (0);
}
