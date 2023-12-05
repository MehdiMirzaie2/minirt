/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:47:03 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/12/04 12:52:09 by mmirzaie         ###   ########.fr       */
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

void	ft_sscanf(const char *tosplit, const char *str, ...)
{
	size_t	i;
	va_list	args;
	char	*substring;
	int		j = 0;
	int		start;

	i = 0;
	va_start(args, str);
	while (str[i])
	{
		while (ft_isspace(tosplit[j]) || tosplit[j] == ',')
			j++;
		start = j;
		while ((tosplit[j] && tosplit[j] != ' ' && tosplit[j] != ',') || tosplit[j] == '.' || tosplit[j] == '-')
			j++;
		if (j == start)
		{
			ft_putstr_fd("not enough arguments in .rt file for object.\n", 2);
			exit(1);
		}
		if (j > start)
			substring = ft_substr(tosplit, start, j);
		while (str[i] != '%')
			i++;
		if (str[i] == '%')
		{
			ft_format(substring, args, str[i + 1]);
			i++;
		}
		i++;
	}
	va_end(args);
}
