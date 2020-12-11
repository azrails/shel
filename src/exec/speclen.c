/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   speclen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/10 21:42:22 by wsallei           #+#    #+#             */
/*   Updated: 2020/12/10 21:42:24 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	char		*getv(char *s, int i, int c)
{
	char	*tmp;
	int		j;

	j = i;
	while (s[j])
	{
		if (s[j] == ' ' || s[j] == '\"' || s[j] == '\\' || s[j] == '\'')
			break ;
		j++;
	}
	tmp = malloc(sizeof(char) * (j - i) + 1);
	while (i < j)
	{
		tmp[c] = s[i];
		i++;
		c++;
	}
	tmp[c] = 0;
	return (tmp);
}

static	int			countenv(t_env *env, char *s, int i)
{
	int		c;
	char	*tmp;
	t_env	*e;

	c = 0;
	e = env;
	tmp = getv(s, i, c);
	while (e)
	{
		if (!(ft_strcmp(tmp, e->key)))
			break ;
		e = e->next;
	}
	if (e)
		c = ft_strlen(e->value);
	if (tmp)
		free(tmp);
	return (c);
}

static	int			lohic(char *s, t_config *cnf, int i, int *count)
{
	char *ss;

	if (s[i + 1] && s[i + 1] == '?')
	{
		ss = ft_itoa(cnf->excode);
		*count += ft_strlen(ss);
		free(ss);
		i += 2;
		if (s[i] == '\0')
			return (-1);
	}
	else
	{
		*count += countenv(cnf->envl, s, ++i);
		while (s[i])
		{
			if (s[i] == ' ' || s[i] == '\'' || s[i] == '\"' || s[i] == '\\')
				return (-1);
			i++;
		}
		if (s[i] == '\0')
			return (-1);
		i--;
	}
	return (i);
}

int					specstrlen(char *s, t_env *env, t_config *cnf)
{
	int		i;
	int		count;
	int		eq;

	i = 0;
	count = 0;
	eq = 0;
	while (s[i])
	{
		eq = checkq(s, i, eq);
		if ((s[i] != '$') || (i != 0 && s[i] == '$' && s[i - 1] == '\\')
			|| (s[i] == '$' && eq == 1))
			count++;
		else if (s[i] == '$' && eq != 1)
		{
			if ((i = lohic(s, cnf, i, &count)) == -1)
				break ;
		}
		i++;
	}
	return (count);
}
