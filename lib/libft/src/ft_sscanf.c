/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:47:03 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/08 11:19:22 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_id(int *num, char *string)
{
	int	number = ft_atoi(string);
	return (*num = number, 1);
}

static int	ft_f(float *num, char *string)
{
	double	number = ft_atof(string);
	return (*num = number, 1);
}

static int	ft_format(char *str, va_list args, const char format)
{
	if (format == 'd' || format == 'i')
		return (ft_id(va_arg(args, int *), str));
	else if (format == 'f')
		return (ft_f(va_arg(args, float *), str));
	return (0);
}

int	ft_sscanf(const char *tosplit, const char *str, ...)
{
	size_t	i;
	va_list	args;
	int		length;
	char	*substring;
	int		j = 0;
	int		start;

	i = 0;
	length = 0;
	va_start(args, str);
	while (str[i])
	{
		while (ft_isspace(tosplit[j]) || tosplit[j] == ',')
			j++;
		start = j;
		// while (tosplit[j] != ' ' && tosplit[j] != ',')
		while ((tosplit[j] >= 48 && tosplit[j] <= 57) || tosplit[j] == '.' || tosplit[j] == '-')
			j++;
		// j++;
		substring = ft_substr(tosplit, start, j);
		while (str[i] != '%')
			i++;
		if (str[i] == '%')
		{
			length += ft_format(substring, args, str[i + 1]);
			i++;
		}
		// while (ft_isspace(tosplit[j]))
		// 	j++;
		i++;
	}
	va_end(args);
	return (length);
}

// int main(void)
// {
// 	int	num[3] = { 0 };
// 	float num2 = 0;

// 	ft_sscanf("10,11,12 13.012", "%d %d %d %f", &num[0], &num[1], &num[2], &num2);
// 	printf("%d %d %d %f\n", num[0], num[1], num[2], num2);
// }