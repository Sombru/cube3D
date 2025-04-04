/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/20 12:35:19 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/29 15:10:17 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// function locates the first occurrence of the null-terminated string small 
// in the string big, where not more than len characters are searched
char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	n;

	if (*small == 0)
		return ((char *)big);
	n = ft_strlen(small);
	while (*big && n <= len)
	{
		if (*big == *small && ft_strncmp(big, small, n) == 0)
			return ((char *)big);
		++big;
		--len;
	}
	return (NULL);
}
