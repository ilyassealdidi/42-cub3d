/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 18:46:45 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/27 19:34:14 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

bool	is_wall(t_game *game, double new_x, double new_y)
{
	int		x;
	int		y;

	x = new_x / TILE_SIZE + game->player.pos.x / TILE_SIZE;
	y = new_y / TILE_SIZE + game->player.pos.y / TILE_SIZE;
	if (x < 0 || y < 0 || x >= game->map.columns || y >= game->map.rows
		|| game->map.map[y][x] == '1')
		return (true);
	return (false);
}

void move_player(void *ptr)
{
	t_game	*game;
	t_point	new_pos;

	game = (t_game *)ptr;
	new_pos.x = cos(game->player.dir) * SPEED;
	new_pos.y = sin(game->player.dir) * SPEED;
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_W) == true)
	{
		if (is_wall(game, new_pos.x, new_pos.y) == false)
		{
			game->player.pos.x += new_pos.x;
			game->player.pos.y += new_pos.y;
		}
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_S) == true)
	{
		if (is_wall(game, -new_pos.x, -new_pos.y) == false)
		{
			game->player.pos.x += -new_pos.x;
			game->player.pos.y += -new_pos.y;
		}
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_A) == true)
	{
		if (is_wall(game, new_pos.y, new_pos.x) == false)
		{
			game->player.pos.x += new_pos.y;
			game->player.pos.y += new_pos.x;
		}
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_D) == true)
	{
		if (is_wall(game, -new_pos.y, -new_pos.x) == false)
		{
			game->player.pos.x += -new_pos.y;
			game->player.pos.y += -new_pos.x;
		}
	}
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_LEFT) == true)
		game->player.dir -= ROTATION_SPEED;
	if (mlx_is_key_down(game->mlx.mlx, MLX_KEY_RIGHT) == true)
		game->player.dir += ROTATION_SPEED;
	normalize_angle(&game->player.dir);
	render_map(game);
}
