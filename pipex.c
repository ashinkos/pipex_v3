/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaouni <aaouni@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 01:08:51 by aaouni            #+#    #+#             */
/*   Updated: 2022/08/02 00:43:41 by aaouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
void	child1(t_varint vint, t_varstr2 vstr, char **env, char *cmd1)
{
	if (vint.pid1 < 0)
			exit(1);
		if (vint.pid1 == 0)
		{
			if(!(vstr.cmd1 = get_path_cmd(cmd1, vstr.path)))
			{
				ft_putstr("command not found: ");
				ft_putstr(cmd1);
				ft_putstr("\n");
				exit(1);
			}
			close(vint.fd[0]);
			dup2(vint.infile, STDIN_FILENO);
			dup2(vint.fd[1], STDOUT_FILENO);
			close(vint.infile);
			close(vint.fd[1]);
			execve(vstr.cmd1[0], vstr.cmd1, env);
			perror("pipex");
			exit(1);
		}
}
void	child2(t_varint vint, t_varstr2 vstr,char **env, char *cmd2)
{
	if (vint.pid2 < 0)
			exit(1);
		if (vint.pid2 == 0)
		{
			if(!(vstr.cmd2 = get_path_cmd(cmd2, vstr.path)))
			{
				ft_putstr("command not found: ");
				ft_putstr(cmd2);
				ft_putstr("\n");
				exit(1);
			}
			close(vint.fd[1]);
			dup2(vint.outfile, STDOUT_FILENO);
			dup2(vint.fd[0], STDIN_FILENO);
			close(vint.outfile);
			close(vint.fd[0]);
			execve(vstr.cmd2[0], vstr.cmd2, env);	
			perror("pipex");
			exit(1);
		}
}

void	infile_error(char *infile, t_varint vint)
{
	if (access(infile, F_OK) < 0)
		{
			perror("pipex");
			exit(1);
		}
		vint.infile = open(infile, O_RDONLY);
		if (vint.infile == -1)
		{
			perror("open");
			exit(1);
		}
}

int main(int argc, char **argv, char **env)
{
	t_varint	vint;
	t_varstr2	vstr;
	
	if (argc == 5)
	{
		vstr.path = get_path_env(env);
		vint.infile = open(argv[1], O_RDONLY);
		infile_error(argv[1], vint);
		vint.outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (pipe(vint.fd) == -1)
			exit(1);
		vint.pid1 = fork();
		child1(vint, vstr, env, argv[2]);
		vint.pid2 = fork();
		child2(vint, vstr,env, argv[3]);
		close(vint.fd[1]);
		close(vint.fd[0]);
		while (waitpid(-1, NULL, 0) > 0)
			;		
	}
	// system("leaks pipex");
	return 0;
}
