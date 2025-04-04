/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pkostura <pkostura@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/25 22:01:26 by pasha             #+#    #+#             */
/*   Updated: 2025/01/26 16:33:33 by pkostura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// duplicates n characters from the string s
char	*ft_strndup(const char *s, size_t n)
{
	char	*new;
	size_t	len;

	len = ft_strlen(s);
	if (n < len)
		len = n;
	new = (char *)malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (NULL);
	ft_memcpy(new, s, len);
	new[len] = '\0';
	return (new);
}
