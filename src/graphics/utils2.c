/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 18:14:56 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/30 18:22:16 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	close_hook(void *param)
{
	clean_exit(param, 0);
}

static void	get_texture(t_game *game)
{
	if (!game->is_horizontal)
	{
		if (is_face_left(game->rayangle))
			game->i = WEST;
		if (is_face_right(game->rayangle))
			game->i = EAST;
	}
	else
	{
		if (is_face_up(game->rayangle))
			game->i = NORTH;
		if (is_face_down(game->rayangle))
			game->i = SOUTH;
	}
}

double get_x(t_game *game)
{
	double x_txt;

	if (game->is_horizontal)
		x_txt = fmod(game->ray_h.x, TILE_SIZE);
	else
		x_txt = fmod(game->ray_v.y, TILE_SIZE);
	return (x_txt);
}

static uint32_t	get_pixel(mlx_texture_t *texture, int x, int y)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;
	int		index;

	if (x >= 0 && (uint32_t)x < texture->width
		&& y >= 0 && (uint32_t)y < texture->height)
	{
		index = (y * texture->width + x) * 4;
		r = texture->pixels[index];
		g = texture->pixels[index + 1];
		b = texture->pixels[index + 2];
		a = texture->pixels[index + 3];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0x000000FF);
}

int	get_texture_color(t_game *game, int y, double wall_height, double x)
{
	t_point			tex;
	t_point			wall;
	uint32_t		color;

	wall.y = (WIN_HEIGHT / 2) - (wall_height / 2);
	get_texture(game);
	tex.y = (y - wall.y) * game->settings.textures[game->i]->height / wall_height;
	color = get_pixel(game->settings.textures[game->i] , x, tex.y);
	return (color);
}