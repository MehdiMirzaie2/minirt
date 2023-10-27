/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_space.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:41:56 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/27 10:43:26 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(int c)
{
	int	is;

	is = c == ' ' || c == '\t' || c == '\v';
	is = is || c == '\r' || c == '\f';
	return (is);
}

int	ft_iterspace(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isspace(str[i]))
			return (i);
		i++;
	}
	return (i);
}

int	ft_isalnum(int c)
{
	if (c <= '9' && c >= '0')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	return (0);
}
