/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 12:17:09 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/12 00:53:47 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	parse_texture(t_game *game, t_list *node)
{
	char	*line;
	int		fd;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	line[ft_strlen(line) - 1] = '\0';
	texture = ft_strdup(line + i);
	if (texture == NULL)
		clean_exit(game, EXIT_FAILURE);
	if (*line == 'N' && game->settings.north == NULL)
		game->settings.north = texture;
	else if (*line == 'S' && game->settings.south == NULL)
		game->settings.south = texture;
	else if (*line == 'W' && game->settings.west == NULL)
		game->settings.west = texture;
	else if (*line == 'E' && game->settings.east == NULL)
		game->settings.east = texture;
	else
	{
		free(texture);
		map_error(game, line, "Texture already set");
	}
	fd = open(texture, O_RDONLY);
	if (fd == -1)
	{
		free(texture);
		map_error(game, line, "Cannot open the file");
	}
}

void	parse_textures(t_game *game, t_list **list)
{
	t_list	*node;

	ft_printf(GREEN"Parsing textures\n"RESET);
	node = *list;
	if (is_color_set(&game->settings))
	{
		if (*((char *)(node->content)) != '\n')
			map_error(game, node, ESEP);
		while (node)
		{
			if (*((char *)(node->content)) != '\n')
				break ;
			node = node->next;
		}
		if (!is_texture(node->content))
			map_error(game, node, "Invalid identifier\n");
	}
	parse_texture(game, node);
	if (node->next == NULL)
		exit_with_error(game, "Missing texture");
	if (!is_texture(node->next->content))
		map_error(game, node->next, "Invalid identifier");
	*list = node->next->next;
}
