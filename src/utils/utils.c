/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:28:16 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/30 14:05:37 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	clean_exit(t_game *game, int status)
{
	free(game->file.name);
	ft_lstclear(&game->file.lines, free);
	if (game->map.map != NULL)
		free_array(game->map.map);
	if (game->mlx.mlx != NULL)
	{
		mlx_close_window(game->mlx.mlx);
		mlx_terminate(game->mlx.mlx);
	}
	if (game->settings.textures[NORTH] != NULL)
		mlx_delete_texture(game->settings.textures[NORTH]);
	if (game->settings.textures[SOUTH] != NULL)
		mlx_delete_texture(game->settings.textures[SOUTH]);
	if (game->settings.textures[WEST] != NULL)
		mlx_delete_texture(game->settings.textures[WEST]);
	if (game->settings.textures[EAST] != NULL)
		mlx_delete_texture(game->settings.textures[EAST]);
	exit(status);
}

void	free_array(char **array)   
{
	int		i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}

