/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 10:16:54 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/18 15:41:51 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	init_mlx(t_game *game)
{
	game->mlx.mlx = mlx_init(game->map.width * TILE_SIZE,
		game->map.height * TILE_SIZE, "cub3D", false);
	if (!game->mlx.mlx)
		exit_with_error(game, "Failed to initialize mlx");
	game->mlx.img = mlx_new_image(game->mlx.mlx, game->map.width * TILE_SIZE, game->map.height * TILE_SIZE);
	if (!game->mlx.img)
		exit_with_error(game, "Failed to create window");
	if (mlx_image_to_window(game->mlx.mlx, game->mlx.img, 0, 0) == -1)
		exit_with_error(game, "Failed to load image to window");
	
}

void draw_player(t_game *cube)
{
    int i;
    int j;
    int center_x;
    int center_y;
    int radius;

    center_x = cube->player.pos.x;
    center_y = cube->player.pos.y;
	// printf("center_x = %d\n", center_x);
	// printf("center_y = %d\n", center_y);
    radius = TILE_SIZE / 7;

    for (i = center_y - radius; i <= center_y + radius; i++)
    {
        for (j = center_x - radius; j <= center_x + radius; j++)
		{
            if (pow(j - center_x, 2) + pow(i - center_y, 2) <= pow(radius, 2))
                mlx_put_pixel(cube->mlx.img, j, i, 0xFF0000FF);
			
		}
    }
}

void	render_map(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < game->map.height * TILE_SIZE)
	{
		j = 0;
		while (j < game->map.width * TILE_SIZE)
		{
			if (ft_strchr("NSWE0 ", game->map.map[i / TILE_SIZE][j / TILE_SIZE]))
				mlx_put_pixel(game->mlx.img, j, i, 0x00FFFFF0);
			else if (game->map.map[i / TILE_SIZE][j / TILE_SIZE] == '1')
				mlx_put_pixel(game->mlx.img, j, i, 0xFFF000FF);
			j++;
		}
		i++;
	}
	draw_player(game);
}

void normalize_angle(t_player *player)
{
	if (player->dir > 2 * M_PI)
		player->dir -= 2 * M_PI;
	// if (player->dir < 0)
	// 	player->dir += 2 * M_PI;
}

bool	is_wall(t_game *game, double new_x, double new_y)
{
	int		x;
	int		y;

	x = new_x / TILE_SIZE + game->player.pos.x / TILE_SIZE;
	y = new_y / TILE_SIZE + game->player.pos.y / TILE_SIZE;
	if (x < 0 || y < 0 || x >= game->map.width || y >= game->map.height)
		return (true);
	if (game->map.map[y][x] == '1')
		return (true);
	return (false);
}

void move_player (void *ptr)
{
	t_game *game = (t_game *)ptr;
	double new_x;
	double new_y;

	new_x = cos (game->player.dir) * SPEED;
	new_y = sin (game->player.dir) * SPEED;
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_W) == true)
	{
		if (is_wall(game, new_x, new_y) == false)
		{
			game->player.pos.x += new_x;
			game->player.pos.y += new_y;
		}
		// game->player.pos.x += cos(game->player.dir) * SPEED;
		// game->player.pos.y += sin(game->player.dir) * SPEED;
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_S) == true)
	{
		if (is_wall(game, -new_x, -new_y) == false)
		{
			game->player.pos.x -= cos(game->player.dir) * SPEED;
			game->player.pos.y -= sin(game->player.dir) * SPEED;
		}
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_A) == true)
	{
		if (is_wall(game, new_y, new_x) == false)
		{
			game->player.pos.x += sin(game->player.dir) * SPEED;
			game->player.pos.y += cos(game->player.dir) * SPEED;
		}
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_D) == true)
	{
		if (is_wall(game, -new_y, -new_x) == false)
		{
			game->player.pos.x -= sin(game->player.dir) * SPEED;
			game->player.pos.y -= cos(game->player.dir) * SPEED;
		}
		// game->player.pos.x -= sin(game->player.dir) * SPEED;
		// game->player.pos.y -= cos(game->player.dir) * SPEED;
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_LEFT) == true)
		game->player.dir -= 2 * M_PI / 180;
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_RIGHT) == true)
		game->player.dir += 2 * M_PI / 180;
	normalize_angle(&game->player);
	render_map(game);
}
void	rungame(t_game *game)
{
	init_mlx(game);
	mlx_loop_hook(game->mlx.mlx, move_player, game);
	mlx_loop(game->mlx.mlx);
}
