/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/18 20:27:54 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static int	get_number(char *str)
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
	char	*ptr;
	int		color;
	char	**rgb;

	ptr = node->content + 2 + ft_strspn(node->content + 2, " ");
	if (!ft_isdigit(*ptr) || !ft_isdigit(ft_strchr(ptr, '\0')[-1]))
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

void	parse_colors(t_game *game, t_list **list)
{
	int		i;

	i = 0;
	while (i < 2)
	{
		if (*list == NULL || ft_strlen((*list)->content) == 0)
			map_error(game, *list, EMISSCOLOR);
		if (!is_color((*list)->content))
			map_error(game, *list, EIDENTIFIER);
		parse_color(game, *list);
		*list = (*list)->next;
		i++;
	}
	if (!is_color_set(&game->settings))
		exit_with_error(game, EMISSCOLOR);
	while (*list != NULL && ft_strlen((*list)->content) == 0)
		*list = (*list)->next;
}
