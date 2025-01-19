/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 00:15:09 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/19 15:55:06 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
bool	check_redirection_syntax(char *input)
{
	char	*redirections;
	char	*special_chars;

	redirections = "<>";
	// check_uclosed_quotes
	while (*input)
	{
		if (ft_strchr(redirections, *input))
		{
			input++;
			while (*input && ft_isspace(*input))
				input++;
			// check_unclosed_quotes
		}
	}
}*/
/**
 * Checks if user input starts or ends with '|', '<' or '>'
 *
 * @param input - user input
 * @return true - if input starts or ends with '|', '<' or '>', false otherwise
 */
/*bool	check_border_special_chars(char *input)
{
	special_chars = "|<>";
	
	while(*input && (*input != '|' && *input != '<' && *input != '>'))
		input++;
	if (*input == '<' && *(input + 1) == '<')
	// check here-doc syntax (move to utils?)
	{
		input += 2;
		while (*input && ft_isspace(*input))
			input++;
		if (!*input)
			return (true);
		return (false);
	}
	else if (ft_strchr(special_chars, input[0])
		|| ft_strchr(special_chars, input[ft_strlen(input) - 1]))
		return (true);
	return (false);
}*/
/**
 * Checks if user input is an empty string or contains only spaces
 *
 * @param input - user input
 * @return true - if input is empty or contains only spaces, false otherwise
 */
bool	check_empty_input(char *input)
{
	while (*input)
	{
		if (!ft_isspace(*input))
			return (false);
		input++;
	}
	return (true);
}

/**
 * Validates user input by checking various conditions
 *
 * @param input (user input)
 * @return true (if user input is valid, false otherwise)
 */
bool	validate_input(char *input)
{
	if (check_empty_input(input))
		return (false);
	if (check_unclosed_quotes(input))
	//|| check_border_special_chars(input))
	{
		write(STDERR_FILENO, "Error\n", 6);
		return (false);
	}
	return (true);
}
