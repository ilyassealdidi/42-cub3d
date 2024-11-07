/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/07 20:53:45 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	get_color(char **rgb)
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

inline bool	is_color(char *line)
{
	return (*line == 'F' || *line == 'C');
}

int	parse_color(t_game *game, t_list **list)
{
	t_list	*tmp;
	char	**rgb;
	char	*line;
	int		color;
	int		i;

	tmp = *list;
	if (is_texture_set(&game->settings))
	{
		while (tmp)
		{
			if (*((char *)(tmp->content)) != '\n')
				break ;
			tmp = tmp->next;
		}
		if (tmp == *list)
			map_error(game, tmp, "Expected new line");
	}
	line = tmp->content;
	if (!is_color(line))
		map_error(game, tmp, "Invalid color identifier");
	i = 1;
	while (line[i] == ' ')
		i++;
	if (i == 1)
		map_error(game, tmp, "Type of information from an element must be separated by one or more space(s)");
	line[ft_strlen(line) - 1] = '\0';
	rgb = ft_split(line + i, ',');
	if (rgb == NULL)
		return (FAILURE);
	color = get_color(rgb);
	if (color == ERROR)
		map_error(game, line, ECOLOR);
	if (*line == 'F' && game->settings.floor == -1)
		game->settings.floor = color;
	else if (*line == 'C' && game->settings.ceiling == -1)
		game->settings.ceiling = color;
	else
		return (map_error(game, line, "Color already set"), ERROR);
	return (SUCCESS);
}
