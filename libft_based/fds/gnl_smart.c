/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_smart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:12:44 by pkostura          #+#    #+#             */
/*   Updated: 2025/03/20 12:23:31 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// returns a line from a file exluding empty line and trims '\n' ending char
char	*gnl_smart(int fd)
{
	char *line;
	int i;
	int only_whitespace;

	line = get_next_line(fd);
	if (!line)
		return (NULL);

	while (line)
	{
		i = 0;
		only_whitespace = 1;
		while (line[i] && line[i] != '\n')
		{
			if (line[i] != ' ' && line[i] != '\t')
			{
				only_whitespace = 0;
				break ;
			}
			i++;
		}
		if (!only_whitespace)
			break ;
		free(line);
		line = get_next_line(fd);
	}
	return (ft_rmlast_char(line, '\n'));
}