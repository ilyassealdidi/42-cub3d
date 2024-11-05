/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:13 by ialdidi           #+#    #+#             */
/*   Updated: 2024/10/05 20:36:08 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	set_defaults(t_game *game)
{
	errno = 0;
	ft_memset(game, 0, sizeof(t_game));
	game->settings.floor = -1;
	game->settings.ceiling = -1;
}

void	destroy_and_exit(t_game *game)
{
	// ft_lstclear(&game->lines, free);
	exit(FAILURE);
}

bool	are_settings_set(t_settings *settings)
{
	return (settings->north
		&& settings->south
		&& settings->west
		&& settings->east
		&& settings->floor != -1
		&& settings->ceiling != -1);
}
