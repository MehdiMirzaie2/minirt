/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:50:12 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/07 16:40:57 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t end)
{
	char *dupped;
	const int length = end - start;
	int	i;
	
	if (ft_strlen(s) < end)
		return (ft_strdup(""));
	dupped = malloc(sizeof(char) * length);
	i = 0;
	while (i < length)
		dupped[i++] = s[start++];
	dupped[i] = '\0';
	return (dupped);
}
