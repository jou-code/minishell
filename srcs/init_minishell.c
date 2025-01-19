/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsoares- <tsoares-@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 05:36:05 by tsoares-          #+#    #+#             */
/*   Updated: 2025/01/19 17:53:40 by jgils            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <readline/readline.h>

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		if (RL_ISSTATE(RL_STATE_READCMD))
			rl_redisplay();
	}
}

/**
 * Main function that reads the user input in a loop and validates the input
 * @return 0 on successful execution
 */
int	main(int argc, char **argv, char **envp)
{
	t_main	*main;
	char	*input;
	char	**split;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	(void)argc;
	(void)argv;
	main = malloc(sizeof(t_main));
	main->envp_list = get_env_list(envp);
	main->envp = env_to_char_array(main->envp_list);
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		else if (input && !has_only_spaces(input))
		{
			if (validate_input(input))
			{
				add_history(input);
				split = metachar_split(input);
				free(input);
				main->cmdtab = get_cmdtable(split, main->envp_list);
				free(split);
				execute_commands(main);
				free_table(main->cmdtab);
			}
		}
	}
	rl_clear_history();
	free_split(main->envp);
	free_env(main->envp_list);
	free(main);
	return (0);
}
