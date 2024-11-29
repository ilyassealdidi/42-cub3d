/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:51:39 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/28 23:57:52 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	set_point(t_point *point, double x, double y)
{
	point->x = x;
	point->y = y;
}

inline bool	is_face_up(double dir)
{
	return (dir > M_PI && dir <= 2 * M_PI);
}

inline bool	is_face_right(double dir)
{
	return (dir < M_PI / 2 || dir > 3 * M_PI / 2);
}

inline bool	is_face_down(double dir)
{
	return (is_face_up(dir) == false);
}

inline bool	is_face_left(double dir)
{
	return (is_face_right(dir) == false);
}
