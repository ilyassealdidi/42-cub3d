/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/26 16:59:10 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static int	get_number(char *str)
{
	int		number;
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERROR);
		i++;
	}
	number = ft_atoi(str);
	if (number > 255 || number < 0)
		return (ERROR);
	return (number);
}

static t_color	get_color(char **rgb)
{
	t_color	color;
	int		number;
	int		i;

	color = 0;
	i = 0;
	while (i < 3)
	{
		if (rgb[i] == NULL)
			return (ERROR);
		number = get_number(rgb[i]);
		if (number == ERROR)
			return (ERROR);
		color = (color << 8) + number;//!
		i++;
	}
	return (color);
}
static char	*parse_texture(t_game *game, t_list *node)
{
	char	*texture;
	char	*line;

	line = node->content + 2 + ft_strspn(node->content + 2, " ");
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
static void	parse_color(t_game *game, t_list *node)
{
	char	*ptr;
	int		color;
	char	**rgb;

	ptr = node->content + 2 + ft_strspn(node->content + 2, " ");
	if (num_char(ptr, ',') != 2)
		map_error(game, node, ECOLOR);
	rgb = ft_split(ptr, ',');
	if (rgb == NULL)
		clean_exit(game, 1);
	color = get_color(rgb);
	free_array(rgb);        
	if (color == ERROR)
		map_error(game, node, ECOLOR);
	if (((char *)node->content)[0] == 'F' && game->settings.floor == -1)
		game->settings.floor = color;
	else if (((char *)node->content)[0] == 'C' && game->settings.ceiling == -1)
		game->settings.ceiling = color;
	else
		map_error(game, node, ECOLORSET);
}

void	parse_colors_textures(t_game *game, t_list **list)
{
	int		fd;

	while (is_color((*list)->content) || is_texture((*list)->content))
	{
		if(is_color((*list)->content))
			parse_color(game, *list);
		else
		{
			fd = open(parse_texture(game, *list), O_RDONLY);
			if (fd == -1)
				map_error(game, *list, EOPEN);
			close(fd);
		}
		*list = (*list)->next;
		while ((*list) != NULL && ft_strlen((*list)->content) == 0)
			*list = (*list)->next;
	}
	if (!is_color((*list)->content) && !is_texture((*list)->content)
		&& (!is_color_set(&game->settings) || !is_texture_set(&game->settings)))
			map_error(game, *list, EIDENTIFIER);
	if (!is_color_set(&game->settings))
		exit_with_error(game, EMISSCOLOR);
	if (!is_texture_set(&game->settings))
		exit_with_error(game, EMISSTEX);
}
