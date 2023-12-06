/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:47:03 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/06 11:28:07 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static void	ft_id(int *num, char *string)
{
	int	number;

	number = ft_atoi(string);
	*num = number;
}

static void	ft_f(float *num, char *string)
{
	double	number;

	number = ft_atof(string);
	*num = number;
}

static void	ft_format(char *str, va_list args, const char format)
{
	if (format == 'd' || format == 'i')
		ft_id(va_arg(args, int *), str);
	else if (format == 'f')
		ft_f(va_arg(args, float *), str);
}

int	sscan_helper(const char *tosplit, int j)
{
	while (ft_isspace(tosplit[j]) || tosplit[j] == ',')
		j++;
	while ((tosplit[j] && tosplit[j] != ' ' && tosplit[j] != ',') || \
		tosplit[j] == '.' || tosplit[j] == '-')
		j++;
	return (j);
}

void	ft_sscanf(const char *tosplit, const char *str, ...)
{
	size_t	i;
	va_list	args;
	char	*substring;
	int		j;
	int		start;

	i = 0;
	j = 0;
	va_start(args, str);
	while (str[i])
	{
		j = sscan_helper(tosplit, j);
		start = j;
		if (j == start)
			exit(1);
		if (j > start)
			substring = ft_substr(tosplit, start, j);
		while (str[i] != '%')
			i++;
		if (str[i++] == '%')
			ft_format(substring, args, str[i + 1]);
		i++;
	}
	va_end(args);
}
