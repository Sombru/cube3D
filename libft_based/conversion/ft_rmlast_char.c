/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rmlast_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:00:29 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/29 15:08:29 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// removes last occurance of char ch from the string
char	*ft_rmlast_char(const char *str, char ch)
{
	char	*last_occurrence;
	char	*result ;
	size_t	length;
	size_t	prefix_length;

	if (!str)
		return (NULL);
	last_occurrence = ft_strrchr(str, ch);
	if (!last_occurrence)
		return (ft_strdup(str));
	length = ft_strlen(str);
	result = malloc(length + 1);
	if (!result)
		return (NULL);
	prefix_length = last_occurrence - str;
	ft_strncpy(result, str, prefix_length);
	ft_strcpy(result + prefix_length, last_occurrence + 1);
	return (result);
}
