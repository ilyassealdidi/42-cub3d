/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/12 00:53:25 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	get_number(char *str)
{
	int		number;
	int		i;

	if (str == NULL)
		return (ERROR);
	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (ERROR);
		i++;
	}
	number = ft_atol(str);
	if (number > 255)
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
		number = get_number(rgb[i]);
		if (number == ERROR)
			return (ERROR);
		color = (color << 8) + number;
		i++;
	}
	return (color);
}

static void	parse_color(t_game *game, t_list *node)
{
	char	*line;
	int		color;
	char	**rgb;

	line = ft_strchr(node->content, ' ') + 1;
	while (*line == ' ')
		line++;
	line[ft_strlen(line) - 1] = '\0';
	rgb = ft_split(line, ',');
	if (rgb == NULL)
		clean_exit(game, 1);
	color = get_color(rgb);
	if (color == ERROR)
		map_error(game, node, ECOLOR);
	if (((char *)node->content)[0] == 'F' && game->settings.floor == -1)
		game->settings.floor = color;
	else if (((char *)node->content)[0] == 'C' && game->settings.ceiling == -1)
		game->settings.ceiling = color;
	else
		map_error(game, node, "Color already set");
}

void	parse_colors(t_game *game, t_list **list)
{
	t_list	*node;

	ft_printf(GREEN"Parsing colors\n"RESET);
	node = *list;
	if (is_texture_set(&game->settings))
	{
		if (*((char *)(node->content)) != '\n')
			map_error(game, node, ESEP);
		while (node)
		{
			if (*((char *)(node->content)) != '\n')
				break ;
			node = node->next;
		}
		if (!is_color(node->content))
			map_error(game, node, "Invalid identifier");
	}
	parse_color(game, node);
	if (node->next == NULL)
		exit_with_error(game, "Missing color");
	if (!is_color(node->next->content))
		map_error(game, node->next, "Invalid identifier");
	parse_color(game, node->next);
	*list = node->next->next;
}
