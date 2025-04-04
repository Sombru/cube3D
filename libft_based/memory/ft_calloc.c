/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sombru <sombru@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/16 11:30:15 by pkostura          #+#    #+#             */
/*   Updated: 2024/12/29 15:09:02 by sombru           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// function allocates memory for an array of nmemb elements of size bytes each 
// and returns a pointer to the allocated memory
void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	if (nmemb != 0 && total_size / nmemb != size)
	{
		return (NULL);
	}
	ptr = malloc (total_size);
	if (ptr != NULL)
	{
		ft_memset(ptr, 0, total_size);
	}
	return (ptr);
}
