/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmirzaie <mmirzaie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 10:33:56 by mmirzaie          #+#    #+#             */
/*   Updated: 2023/10/27 10:34:09 by mmirzaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double ft_atof(char *str)
{
    double	res;
	double	power;
    int		i;
	int		sign;

	i = 0;
	sign = 1;
	res = 0;
	power = 1.0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10.0) + (str[i] - '0');
		i++;
	}
    if (str[i] == '.')
        ++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		power *= 10.0;
		i++;
	}
    return (sign * res / (power));
}
