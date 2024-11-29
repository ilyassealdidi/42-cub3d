/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:16:54 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/29 17:12:28 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static void	cast_rays(t_game *game)
{
	double	rayangle;
	double	distance;
	int		i;

	rayangle = game->player.dir - (FOV / 2);
	if (rayangle < 0)
		rayangle += 2 * M_PI;
	i = 0;
	double distance_proj = (WIN_WIDTH / 2) / tan(FOV / 2);
	while (i < WIN_WIDTH)
	{
		distance = get_distance(game, rayangle) * cos(game->player.dir - rayangle);
		double wall_height = (TILE_SIZE / distance) * distance_proj;
		int wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
		if (wall_top < 0)
			wall_top = 0;
		int wall_bottom = (WIN_HEIGHT / 2) + (wall_height / 2);
		if (wall_bottom > WIN_HEIGHT)
			wall_bottom = WIN_HEIGHT;
		int j = wall_top;
		while (j < wall_bottom)
		{
			mlx_put_pixel(game->mlx.img, i, j, 0x1F1F1FFF);
			j++;
		}
		rayangle += FOV / WIN_WIDTH;
		i++;
	}
}

static void	draw_background(t_game *game)
{
	int		i;
	int		j;

	i = -1;
	while (i++ < WIN_HEIGHT / 2)
	{
		j = 0;
		while (j < WIN_WIDTH)
			mlx_put_pixel(game->mlx.img, j++, i, game->settings.ceiling);
	}
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
	// static t_point	old_pos;
	// static double	old_dir;

	game = (t_game *)ptr;
	// if (old_pos.x == game->player.pos.x && old_pos.y == game->player.pos.y
	// 	&& old_dir == game->player.dir)
	// 	return ;
	draw_background(game);
	cast_rays(game);
	// set_point(&old_pos, game->player.pos.x, game->player.pos.y);
	// old_dir = game->player.dir;
}

void	close_hook(void *param)
{
	clean_exit(param, 0);
}

void	rungame(t_game *game)
{
	init_mlx(game);
	render_map(game);
	// mlx_loop_hook(game->mlx.mlx, render_map, game);
	mlx_loop_hook(game->mlx.mlx, key_hook, game);
	mlx_close_hook(game->mlx.mlx, close_hook, game);
	mlx_loop(game->mlx.mlx);
}
