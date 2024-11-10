/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 18:28:16 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/10 12:18:04 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

bool    isset(void *ptr)
{
    return (ptr != NULL);
}

void	clean_exit(t_game *game, int status)
{
	free(game->file.name);
	free(game->settings.north);
	free(game->settings.south);
	free(game->settings.west);
	free(game->settings.east);
	ft_lstclear(&game->file.lines, free);
	ft_lstclear(&game->map.map, free);
	exit(status);
}
