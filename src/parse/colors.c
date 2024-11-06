/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/06 13:49:48 by ialdidi          ###   ########.fr       */
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

int	parse_color(t_game *game, char *line)
{
	char	**rgb;
	int		color;
	int		i;

	i = 1;
	while (line[i] == ' ')
		i++;
	line[ft_strlen(line) - 1] = '\0';
	rgb = ft_split(line + i, ',');
	if (rgb == NULL)
		return (FAILURE);
	color = get_color(rgb);
	if (color == ERROR)
		return (print_map_error(game, line, ECOLOR), ERROR);
	if (*line == 'F' && game->settings.floor == -1)
		game->settings.floor = color;
	else if (*line == 'C' && game->settings.ceiling == -1)
		game->settings.ceiling = color;
	else
		return (print_map_error(game, line, "Color already set"), ERROR);
	return (SUCCESS);
}
