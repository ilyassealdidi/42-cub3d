/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:16:54 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/27 22:19:43 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	put_pixel(mlx_image_t *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= img->width || y < 0 || y >= img->height)
		return ;
	mlx_put_pixel(img, x, y, RAY_COLOR);
}

void draw_player(t_game *game)
{
    int	i;
    int	j;
    int	center_x;
    int	center_y;
    int	radius;

    center_x = game->player.pos.x;
    center_y = game->player.pos.y;
    radius = TILE_SIZE / 7;
    for (i = center_y - radius; i <= center_y + radius; i++)
    {
        for (j = center_x - radius; j <= center_x + radius; j++)
		{
            if (pow(j - center_x, 2) + pow(i - center_y, 2) <= pow(radius, 2))
                mlx_put_pixel(game->mlx.img, j, i, PLAYER_COLOR);
		}
    }
}

void	cast_rays(t_game *game)
{
	t_point	step;
	double	rayangle;
	double	distance;
	int		i;

	rayangle = game->player.dir - (FOV / 2);
	if (rayangle < 0)
		rayangle += 2 * M_PI;
	i = 0;
	while (i < game->mlx.width)
	{
		distance = get_distance(game, rayangle);
		int j = -1;
		while (++j < distance)
			put_pixel(game->mlx.img, game->player.pos.x + cos(rayangle) * j, game->player.pos.y + sin(rayangle) * j, RAY_COLOR);
		rayangle += FOV / game->mlx.width;
		i++;
	}
}

void	draw_background(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->mlx.height / 2)
	{
		j = 0;
		while (j < game->mlx.width)
		{
			mlx_put_pixel(game->mlx.img, j, i, game->settings.ceiling);
			j++;
		}
		i++;
	}
	while (i < game->mlx.height)
	{
		j = 0;
		while (j < game->mlx.width)
		{
			mlx_put_pixel(game->mlx.img, j, i, game->settings.floor);
			j++;
		}
		i++;
	}
}

void	render_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->mlx.height)
	{
		j = 0;
		while (j < game->mlx.width)
		{
			if (ft_memchr("NSWE0 ", game->map.map[i / TILE_SIZE][j / TILE_SIZE], 6))
				mlx_put_pixel(game->mlx.img, j, i, SPACE_COLOR);
			else
				mlx_put_pixel(game->mlx.img, j, i, WALL_COLOR);
			j++;
		}
		i++;
	}
	draw_background(game);
	draw_player(game);
	cast_rays(game);
}

void	init_mlx(t_game *game)
{
	game->mlx.height = game->map.rows * TILE_SIZE;
	game->mlx.width = game->map.columns * TILE_SIZE;
	game->mlx.mlx = mlx_init(game->mlx.width, game->mlx.height, WIN_TITLE, false);
	if (game->mlx.mlx == NULL)
		exit_with_error(game, "Failed to initialize mlx");
	game->mlx.img = mlx_new_image(game->mlx.mlx, game->mlx.width, game->mlx.height);
	if (game->mlx.img == NULL)
		exit_with_error(game, "Failed to create window");
	if (mlx_image_to_window(game->mlx.mlx, game->mlx.img, 0, 0) == -1)
		exit_with_error(game, "Failed to load image to window");
}

void	rungame(t_game *game)
{
	init_mlx(game);
	mlx_loop_hook(game->mlx.mlx, move_player, game);
	mlx_loop(game->mlx.mlx);
}
