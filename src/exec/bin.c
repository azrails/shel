/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 12:04:39 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/11 12:08:09 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	void		mess(char *p, int fd, DIR *cat)
{
	if (!p || !ft_strchr(p, '/'))
		ft_putendl_fd(": \e[1;38;5;202mcommand not found\e[0m", 2);
	else if (fd == -1 && !cat)
		ft_putendl_fd(": \e[1;38;5;202mNo such file or directory\e[0m", 2);
	else if (fd == -1 && cat)
		ft_putendl_fd(": \e[1;38;5;202mis a directory\e[0m", 2);
	else if (fd > -1 && !cat)
		ft_putendl_fd(": \e[1;38;5;202mPermission denied\e[0m", 2);
}

static	int			errs(char *p, char *func)
{
	int fd;
	int status;
	DIR	*cat;

	status = 0;
	cat = 0;
	fd = -1;
	if (p)
	{
		fd = open(p, O_WRONLY);
		cat = opendir(p);
	}
	ft_putstr_fd(func, 2);
	mess(p, fd, cat);
	if ((!p || ft_strchr(p, '/') == NULL) || (fd == -1 && cat == NULL))
		status = 127;
	else
		status = 126;
	if (cat)
		closedir(cat);
	closefd(fd);
	return (status);
}

int					bin(char *p, char **targ, t_config *cnf, t_tok *pnt)
{
	int status;

	status = 0;
	cnf->pid = fork();
	if (cnf->pid == 0)
	{
		if (p && ft_strchr(p, '/'))
			execve(p, targ, cnf->env);
		status = errs(p, targ[0]);
		exit(status);
	}
	else
		waitpid(cnf->pid, &status, 0);
	status = (status == 32256 || status == 32512) ? status / 256 : !!status;
	return (status);
}
