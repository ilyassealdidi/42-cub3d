/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/09 19:03:42 by ialdidi          ###   ########.fr       */
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

static int	get_color(char **rgb)
{
	int		color;
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

void	parse_color(t_game *game, t_list *node)
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
		map_error(game, line, ECOLOR);
	if (*line == 'F' && game->settings.floor == -1)
		game->settings.floor = color;
	else if (*line == 'C' && game->settings.ceiling == -1)
		game->settings.ceiling = color;
	else
		map_error(game, line, "Color already set");
}

void	parse_colors(t_game *game, t_list **list)
{
	t_list	*tmp;

	ft_printf("Parsing colors\n");
	tmp = *list;
	if (is_texture_set(&game->settings))
	{
		if (*((char *)(tmp->content)) != '\n')
			map_error(game, tmp, "Expected empty line");
		while (tmp)
		{
			if (*((char *)(tmp->content)) != '\n')
				break ;
			tmp = tmp->next;
		}
		if (tmp == *list)
			map_error(game, tmp, "type of element must be separated by one or more empty line(s)");
		if (!is_color(tmp->content))
			map_error(game, tmp, "Invalid identifier");
	}
	parse_color(game, tmp);
	if (tmp->next == NULL || !is_color(tmp->next->content))
		map_error(game, tmp, "Invalid identifier");
	parse_color(game, tmp->next);
}
