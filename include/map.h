/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaeshin <jaeshin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:27:32 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/11/08 22:16:01 by jaeshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

#include "minirt.h"

enum	e_identifier
{
	E_TTSP = 's' * 'p',
	E_TTPL = 'p' * 'l',
	E_TTCY = 'c' * 'y',
};

int	parse(t_map **map, char	*fname);

#endif
