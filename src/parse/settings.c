/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/30 14:06:15 by ialdidi          ###   ########.fr       */
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

static int	get_color(char **rgb)
{
	int		color;
	int		number;
	int		i;

	i = 0;
	color = 0;
	while (i < 3)
	{
		if (rgb[i] == NULL)
			return (ERROR);
		number = get_number(rgb[i]);
		if (number == ERROR)
			return (ERROR);
		color += number;
		color = color << 8;
		i++;
	}
	color += 255;
	return (color);
}

static void	parse_texture(t_game *game, t_list *node)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(node->content + 2
		+ ft_strspn(node->content + 2, " "));
	if (texture == NULL)
		map_error(game, node, ETEXLOAD);
	if (*(char *)(node->content) == 'N'
		&& !game->settings.textures[NORTH])
		game->settings.textures[NORTH] = texture;
	else if (*(char *)(node->content) == 'S'
		&& !game->settings.textures[SOUTH])
		game->settings.textures[SOUTH] = texture;
	else if (*(char *)(node->content) == 'W'
		&& !game->settings.textures[WEST])
		game->settings.textures[WEST] = texture;
	else if (*(char *)(node->content) == 'E'
		&& !game->settings.textures[EAST])
		game->settings.textures[EAST] = texture;
	else
		map_error(game, node, ETEXSET);
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
	while (is_color((*list)->content) || is_texture((*list)->content))
	{
		if(is_color((*list)->content))
			parse_color(game, *list);
		else
			parse_texture(game, *list);
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
