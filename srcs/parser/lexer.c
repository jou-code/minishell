#include "../../includes/minishell.h"

int	count_tokens(char *user_input)
{
	int		count;
	int		start;
	int		quote;
	int		tokens;
	char	*input;

	count = 0;
	tokens = 0;
	input = strtrim_space(user_input);
	while (input && input[count] != '\0')
	{
		start = count;
		if (is_operator(input[start]))
		{
			count++;
			if (is_operator(input[count]) && input[count] == input[start])
				count++;
		}
		else if (!is_metachar(input[start]))
		{
			while (input[count] != '\0' && !is_metachar(input[count]))
			{
				if (is_quote(input[count]))
				{
					quote = count++;
					while (input[count] != input[quote])
						count++;
				}
				count++;
			}
		}
		tokens++;
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	free(input);
	return (tokens);
}

char	**metachar_split(char *user_input)
{
	int		count;
	int		start;
	int		token;
	int		quote;
	char	**array;
	char	*input;

	count = 0;
	start = -1;
	token = 0;
	input = strtrim_space(user_input);
	array = (char **)malloc((count_tokens(input) + 1) * sizeof(char *));
	while (input && input[count] != '\0')
	{
		start = count;
		if (is_operator(input[start]))
		{
			count++;
			if (is_operator(input[count]) && input[count] == input[start])
				count++;
		}
		else if (!is_metachar(input[start]))
		{
			while (input[count] != '\0' && !is_metachar(input[count]))
			{
				if (is_quote(input[count]))
				{
					quote = count++;
					while (input[count] != input[quote])
						count++;
				}
				count++;
			}
		}
		else if (!is_space(input[start]))
		{
			while (input[count] != '\0' && !is_metachar(input[count])
				&& !is_quote(input[count]))
				count++;
		}
		array[token++] = substr_by_address(&input[start], (count - start));
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	array[token] = NULL;
	free(input);
	return (array);
}
