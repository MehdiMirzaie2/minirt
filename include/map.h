/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mehdimirzaie <mehdimirzaie@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 12:27:32 by mehdimirzai       #+#    #+#             */
/*   Updated: 2023/10/26 12:36:47 by mehdimirzai      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

enum	e_identifier
{
	E_TTA = 'A',
	E_TTC = 'C',
	E_TTL = 'L',
	E_TTSP = 'S' + 'P',
	E_TTPL = 'p' + 'l',
	E_TTCY = 'c' + 'y',
	E_TTLT = 1 << 3,
	E_TTRGB = 1 << 4,
	E_TTVP = 1 << 5,
	E_TTNO = 1 << 6,
	E_TTFOV = 1 << 7,
	
};


#endif