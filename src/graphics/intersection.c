/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 17:07:47 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/30 14:24:50 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static bool	is_wall(t_game *game, double x, double y)
{
	int		i;
	int		j;

	i = y / TILE_SIZE;
	j = x / TILE_SIZE;
	return (i < 0 || j < 0 || i >= game->map.rows || j >= game->map.columns
		|| game->map.map[i][j] == '1');
}

static double	get_horizontal_intersection(t_game *game, double rayangle)
{
	t_point	intersect;
	t_point	step;

	intersect.y = (floor(game->player.pos.y / TILE_SIZE)
		+ is_face_down(rayangle)) * TILE_SIZE;
	intersect.x = game->player.pos.x
		+ (intersect.y - game->player.pos.y) / tan(rayangle);
	intersect.y -= is_face_up(rayangle);
	step.x = TILE_SIZE / tan(rayangle);
	if (step.x < 0 && is_face_right(rayangle))
		step.x = -step.x;
	else if (step.x > 0 && is_face_left(rayangle))
		step.x = -step.x;
	step.y = TILE_SIZE * (1 - 2 * is_face_up(rayangle));
	while (!is_wall(game, intersect.x, intersect.y))
	{
		intersect.x += step.x;
		intersect.y += step.y;
	}
	game->ray_h = intersect;
	return (sqrt(pow(intersect.x - game->player.pos.x, 2)
		+ pow(intersect.y - game->player.pos.y, 2)));
}

static double	get_vertical_intersection(t_game *game, double rayangle)
{
	t_point	intersect;
	t_point	step;

	intersect.x = (floor(game->player.pos.x / TILE_SIZE) + is_face_right(rayangle)) * TILE_SIZE;
	intersect.y = game->player.pos.y + tan(rayangle) * (intersect.x - game->player.pos.x);
	step.x = TILE_SIZE * (is_face_right(rayangle) - is_face_left(rayangle));
	step.y = TILE_SIZE * tan(rayangle);
	if (step.y < 0 && is_face_down(rayangle))
		step.y = -step.y;
	else if (step.y > 0 && is_face_up(rayangle))
		step.y = -step.y;
	intersect.x -= is_face_left(rayangle);
	while (!(is_wall(game, intersect.x, intersect.y)))
	{
		intersect.x += step.x;
		intersect.y += step.y;
	}
	game->ray_v = intersect;
	return (sqrt(pow(intersect.x - game->player.pos.x, 2)
		+ pow(intersect.y - game->player.pos.y, 2)));
}

double	get_distance(t_game *game)
{
	double	rayangle;
	double	distance;
	double	hdistance;
	double	vdistance;

	rayangle = game->rayangle;
	hdistance = get_horizontal_intersection(game, rayangle);
	vdistance = get_vertical_intersection(game, rayangle);
	if (hdistance < vdistance)
	{
		distance = hdistance;
		game->ray = game->ray_h;
	}
	else
	{
		distance = vdistance;
		game->ray = game->ray_v;
	}
	game->is_horizontal = hdistance < vdistance;
	return (distance * cos(game->player.dir - rayangle));
}
