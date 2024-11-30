/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:16:54 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/30 18:27:30 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static void	cast_rays(t_game *game)
{
	double	wall_height;
	int		wall_top;
	int		wall_bottom;
	int		i;

	game->rayangle = game->player.dir - (FOV / 2);
	if (game->rayangle < 0)
		game->rayangle += 2 * M_PI;
	i = -1;
	while (++i < WIN_WIDTH)
	{
		wall_height = (TILE_SIZE / get_distance(game)) * DIST_PROJ;
		wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
		wall_top = wall_top * (wall_top >= 0);
		wall_bottom = (WIN_HEIGHT / 2) + (wall_height / 2);
		if (wall_bottom > WIN_HEIGHT)
			wall_bottom = WIN_HEIGHT;
		while (wall_top < wall_bottom)
		{
			mlx_put_pixel(game->mlx.img, i, wall_top,
				get_texture_color(game, wall_top, wall_height, get_x(game)));
			wall_top++;
		}
		game->rayangle += FOV / WIN_WIDTH;
	}
}

static void	draw_background(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
			mlx_put_pixel(game->mlx.img, j++, i, game->settings.ceiling);
		i++;
	}
	i = WIN_HEIGHT / 2;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
			mlx_put_pixel(game->mlx.img, j++, i, game->settings.floor);
		i++;
	}
}

static void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, WIN_TITLE, false);
	if (game->mlx.mlx == NULL)
		exit_with_error(game, "Failed to initialize mlx");
	game->mlx.img = mlx_new_image(game->mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
	if (game->mlx.img == NULL)
		exit_with_error(game, "Failed to create window");
	if (mlx_image_to_window(game->mlx.mlx, game->mlx.img, 0, 0) == -1)
		exit_with_error(game, "Failed to load image to window");
}

void render_map(void *ptr)
{
	t_game			*game;
	static t_point	old_pos;
	static double	old_dir;

	game = (t_game *)ptr;
	if (old_pos.x == game->player.pos.x && old_pos.y == game->player.pos.y
		&& old_dir == game->player.dir)
		return ;
	draw_background(game);
	cast_rays(game);
	set_point(&old_pos, game->player.pos.x, game->player.pos.y);
	old_dir = game->player.dir;
}

void	rungame(t_game *game)
{
	init_mlx(game);
	render_map(game);
	mlx_loop_hook(game->mlx.mlx, key_hook, game);
	mlx_close_hook(game->mlx.mlx, close_hook, game);
	mlx_loop(game->mlx.mlx);
}
