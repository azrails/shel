/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_skipspace.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wsallei <wsallei@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 20:28:18 by wsallei           #+#    #+#             */
/*   Updated: 2020/11/21 20:28:20 by wsallei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_skipspace(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n' ||
		line[i] == '\f')
		i++;
	return (i);
}
