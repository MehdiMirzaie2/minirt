#include <stdio.h>
#include "libft.h"
#include "get_next_line.h"
#include "mlx.h"
#include "map.h"

int	main(int ac, char **av)
{
	t_map *map;

	map = NULL;
	if (ac == 2)
	{
		map = malloc(sizeof(t_map));
		parse(&map, av[1]);
	}
	return (0);
}

// #include "../libft/include/libft.h"
// # include <stdarg.h>
// # include <unistd.h>
// # include <stdint.h>
// #include <stdio.h>

// int	ft_id(int *num, char *string)
// {
// 	int	number = ft_atoi(string);
// 	return (*num = number, 1);
// }

// int	ft_f(float *num, char *string)
// {
// 	double	number = ft_atof(string);
// 	return (*num = number, 1);
// }

// int	ft_format(char *str, va_list args, const char format)
// {
// 	if (format == 'd' || format == 'i')
// 		return (ft_id(va_arg(args, int *), str));
// 	else if (format == 'f')
// 		return (ft_f(va_arg(args, float *), str));
// 	return (0);
// }

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
// 		start = j;
// 		while (tosplit[j] != ' ' && tosplit[j] != ',')
// 			j++;
// 		j++;
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

// 	ft_sscanf("0.2 255,255,255", "%f %d %d %d", &num2, &num[0], &num[1], &num[2]);
// 	printf("%f %d %d %d\n", num2, num[0], num[1], num[2]);
// }