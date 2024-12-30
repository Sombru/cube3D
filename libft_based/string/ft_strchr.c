/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 11:16:31 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/29 15:09:22 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// The strchr() function returns a pointer to 
// the first occurrence of the character c in the string s.
char	*ft_strchr(const char *s, int c)
{
	char	*ptr;

	ptr = (char *)s;
	while (*ptr)
	{
		if (*ptr == (unsigned char)c)
			return (ptr);
		ptr++;
	}
	if (c == 0)
		return (ptr);
	return (NULL);
}
