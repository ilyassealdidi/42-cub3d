/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:17:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/12 13:10:40 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static char	*parse_texture(t_game *game, t_list *node)
{
	char	*texture;
	char	*line;

	line = ft_strrchr(node->content, ' ') + 1;
	texture = ft_strdup(line);
	if (texture == NULL)
		exit_with_error(game, NULL);
	if (*(char *)(node->content) == 'N' && game->settings.north == NULL)
		game->settings.north = texture;
	else if (*(char *)(node->content) == 'S' && game->settings.south == NULL)
		game->settings.south = texture;
	else if (*(char *)(node->content) == 'W' && game->settings.west == NULL)
		game->settings.west = texture;
	else if (*(char *)(node->content) == 'E' && game->settings.east == NULL)
		game->settings.east = texture;
	else
	{
		free(texture);
		map_error(game, node, ETEXSET);
	}
	return (texture);
}

void	parse_textures(t_game *game, t_list **list)
{
	int		fd;
	int		i;

	i = 0;
	while (i < 4 && *list != NULL)
	{
		if (ft_strlen((*list)->content) == 0)
			map_error(game, *list, EMISSTEX);
		if (!is_texture((*list)->content))
			map_error(game, *list, EIDENTIFIER);
		fd = open(parse_texture(game, *list), O_RDONLY);
		if (fd == -1)
			map_error(game, *list, EOPEN);
		close(fd);
		*list = (*list)->next;
		i++;
	}
	if (!is_texture_set(&game->settings))
		exit_with_error(game, EMISSTEX);
}
