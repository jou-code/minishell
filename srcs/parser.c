#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;
	i = 0;

	while (str && str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strtrim(char *s1)
{
	char	*trim;
	int		start;
	int		end;
	int		i;

	i = 0;
	start = 0;
	end = ft_strlen(s1) - 1;
	while (s1[start] && s1[start] == ' ')
		start++;
	while (end > start && s1[end] == ' ')
		end--;
	trim = (char *) malloc((end - start + 2) * sizeof(char));
	if (!trim)
		return (NULL);
	while (start <= end)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}

char	*ft_substr(char *str, int len)
{
	int	i;
	char	*substr;

	i = 0;
	substr = malloc ((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	while (i < len)
	{
		substr[i] = str[i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	is_basic(char c)
{
	return (!(is_special(c)) && !(is_quote(c)) && !(is_space(c)));
}

/*
 * count the amount of tokens in an input
 */
int	count_tokens(char *input)
{
	int	count = 0;
	int	start = 0;
	int	tokens = 0;

	while (input && input[count] != '\0')
	{
		start = count;
		count++;
		if (is_special(input[start]))
		{
			if (is_special(input[count]) && input[count] == input[start])
				count++;
		}
		else if (is_quote(input[start]))
		{
			while (input[count] != '\0' && input[count] != input[start])
				count++;
			count++;
		}
		else if (is_basic(input[start]))
		{
			while (input[count] != '\0' && is_basic(input[count]))
				count++;
		}
		tokens++;
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	return (tokens);
}

/*
* splits user_input into an array of tokens.
* lexical analisis divides tokens by: >, <, |, <<, >>, '...', "..." and SPACE
*/
char	**tokenizer(char *user_input)
{
	int	count = 0;
	int	start = 0;
	int	token = 0;
	char	**array;
	char	*input;
	
	// expansao de variaveis? ver no futuro
	// $
	input = ft_strtrim(user_input);
	array = (char **)malloc((count_tokens(input) + 1) * sizeof(char *));
	// printf("\n\ntokens + null = %i\n\n\n", count_tokens(input));
	while (input && input[count] != '\0')
	{
		start = count;
		count++;
		if (is_special(input[start]))
		{
			if (is_special(input[count]) && input[count] == input[start])
			// se eh especial (<,|,>) e se o proximo eh igual (>>, <<)
			{
				count++;
			}
		}
		else if (is_quote(input[start]))
		{
			while (input[count] != '\0' && input[count] != input[start])
			{
				count++;
			}
			count++;
		}
		else if (is_basic(input[start]))
		{
			while (input[count] != '\0' && is_basic(input[count]))
			{
				count++;
			}
		}
		array[token++] = ft_substr(&input[start], (count - start));
		// printf("\ntoken%i - count: %i | start: %i\n\n", token, count, start);
		if (is_space(input[count]))
			while (is_space(input[count]))
				count++;
	}
	array[token] = NULL;
	free(input);
	return (array);
}

void	free_split(char **array)
{
	int	i = 0;

	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	print_split(char **array)
{
	int	i = 0;

	while (array[i] != NULL)
	{
		printf("%d: <%s>\n", i, array[i]);
		i++;
	}
}

int	main(void)
{
	int	i = 0;
	char	*input = "token 1 2 '3' << | >| >> '    50 |>'";
	char	**tokens;
	
	tokens = tokenizer(input);
	free_split(tokens);
	return (0);
}
