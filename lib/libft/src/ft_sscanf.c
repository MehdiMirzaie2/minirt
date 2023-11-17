/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sscanf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 13:47:03 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/11/16 20:53:24 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
static int	ft_id(int *num, char *string)
{
	int	number = ft_atoi(string);
	*num = number;
	// printf("\n%s\t%d\n", string, *num);
	return (1);
}

static int	ft_f(float *num, char *string)
{
	double	number = ft_atof(string);
	*num = number;
	// printf("\n%s\t%f\n", string, *num);
	return (1);
}

static int	ft_format(char *str, va_list args, const char format)
{
	if (format == 'd' || format == 'i')
		return (ft_id(va_arg(args, int *), str));
	else if (format == 'f')
		return (ft_f(va_arg(args, float *), str));
	return (0);
}

// static void	ft_allocate(char **tab, char const *s, char sep)
// {
// 	char		**tab_p;
// 	char const	*tmp;

// 	tmp = s;
// 	tab_p = tab;
// 	while (*tmp)
// 	{
// 		while (*s == sep)
// 			++s;
// 		tmp = s;
// 		while (*tmp && *tmp != sep)
// 			++tmp;
// 		if (*tmp == sep || tmp > s)
// 		{
// 			*tab_p = ft_substr(s, 0, tmp - s);
// 			s = tmp;
// 			++tab_p;
// 		}
// 	}
// 	*tab_p = NULL;
// }

int	ft_sscanf(const char *tosplit, const char *str, ...)
{
	size_t	i;
	va_list	args;
	int		length;
	char	*substring;
	int		j = 0;
	int		start;
	// char const *tmp;

	// tmp = tosplit;
	i = 0;
	length = 0;
	va_start(args, str);
	while (str[i])
	{
		while (ft_isspace(tosplit[j]) || tosplit[j] == ',')
		// while (tosplit[j] == ' ' || tosplit[j] == ',')
			j++;
		start = j;
		while ((tosplit[j] && tosplit[j] != ' ' && tosplit[j] != ',') || tosplit[j] == '.' || tosplit[j] == '-')
			j++;
		if (j > start)
		{
			substring = ft_substr(tosplit, start, j);
			// printf("hi %s\n", substring);
		}
		while (str[i] != '%')
			i++;
		if (str[i] == '%')
		{
			length += ft_format(substring, args, str[i + 1]);
			i++;
		}
		i++;
	}
	va_end(args);
	return (length);
}


// int	ft_sscanf(const char *tosplit, const char *str, ...)
// {
// 	size_t	i;
// 	va_list	args;
// 	int		length;
// 	char	*substring;
// 	int		j = 0;
// 	int		start;

// 	i = 0;
// 	length = 0;
// 	va_start(args, str);
// 	while (str[i])
// 	{
// 		while (ft_isspace(tosplit[j]) || tosplit[j] == ',')
// 			j++;
// 		start = j;
// 		while ((tosplit[j] >= 48 && tosplit[j] <= 57) || tosplit[j] == '.' || tosplit[j] == '-')
// 			j++;
// 		substring = ft_substr(tosplit, start, j);
// 		while (str[i] != '%')
// 			i++;
// 		if (str[i] == '%')
// 		{
// 			length += ft_format(substring, args, str[i + 1]);
// 			i++;
// 		}
// 		i++;
// 	}
// 	va_end(args);
// 	return (length);
// }

// int main(void)
// {
// 	int	num[3] = { 0 };
// 	float num2 = 0;

// 	ft_sscanf("10,11,12 13.012", "%d %d %d %f", &num[0], &num[1], &num[2], &num2);
// 	printf("%d %d %d %f\n", num[0], num[1], num[2], num2);
// }