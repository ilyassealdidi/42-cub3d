/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:28:16 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/18 17:17:33 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	clean_exit(t_game *game, int status)
{
	free(game->file.name);
	free(game->settings.north);
	free(game->settings.south);
	free(game->settings.west);
	free(game->settings.east);
	ft_lstclear(&game->file.lines, free);
	if (game->map.map != NULL)
		free_array(game->map.map);
	exit(status);
}

void	free_array(char **array)
{
	int		i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
