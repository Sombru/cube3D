/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 10:21:25 by pasha             #+#    #+#             */
/*   Updated: 2024/12/29 15:08:02 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// Copy an array of strings
char    **ft_arrcpy(char **array)
{
    char    **new_array;
    int     i;

    i = 0;
    if (!array)
        return (NULL);
    while (array[i])
        i++;
    new_array = malloc((i + 1) * sizeof(char *));
    if (!new_array)
        return (NULL);
    i = 0;
    while (array[i])
    {
        new_array[i] = ft_strdup(array[i]);
        i++;
    }
    new_array[i] = NULL;
    return (new_array);
}
