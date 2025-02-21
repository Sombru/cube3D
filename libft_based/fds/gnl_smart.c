/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_smart.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 12:12:44 by pkostura          #+#    #+#             */
/*   Updated: 2025/02/14 13:21:55 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// returns a line from a file exluding empty line and trims '\n' ending char 
char	*gnl_smart(int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		return (NULL);
    while (line && line[0] == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    return (ft_rmlast_char(line, '\n'));
	
}
