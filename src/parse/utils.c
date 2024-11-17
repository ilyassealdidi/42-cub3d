/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:13 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/17 11:03:33 by ialdidi          ###   ########.fr       */
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

bool	is_color(char *line)
{
	if (line == NULL)
		return (false);
	return (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0);
}

bool	is_texture(char *line)
{
	if (line == NULL)
		return (false);
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

bool is_color_set(t_settings *settings)
{
	return (settings->floor != -1 && settings->ceiling != -1);
}

bool is_texture_set(t_settings *settings)
{
	return (settings->north != NULL && settings->south != NULL
		&& settings->west != NULL && settings->east != NULL);
}

