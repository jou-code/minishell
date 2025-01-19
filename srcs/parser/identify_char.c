#include "../../includes/minishell.h"

int	is_operator(char c)
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

int	is_metachar(char c)
{
	return (is_operator(c) || is_space(c));
}

/* returns if is a valid name for an enviroment variable ([a-z], [A-Z], '_',
		[0-9]) */
int	is_name(char c)
{
	return ((c == '_') || ft_isalnum(c));
}
