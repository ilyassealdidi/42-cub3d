/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 13:49:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/18 22:12:12 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static int	get_number(char *str)
{
	int		number;

	if (str == NULL || ft_strlen(str) == 0
		|| ft_strlen(str) != ft_strspn(str, "0123456789"))
		return (ERROR);
	number = ft_atol(str);
	if (number > 255)
		return (ERROR);
	return (number);
}

static t_color	get_color(t_game *game, char *ptr)
{
	t_color	color;
	char	*sub;
	int		number;
	int		len;
	int		i;

	color = 0;
	i = 0;
	while (i < 3)
	{
		len = ft_strcspn(ptr, ",");
		sub = ft_substr(ptr, 0, len);
		if (sub == NULL)
			exit_with_error(game, NULL);
		number = get_number(sub);
		free(sub);
		if (number == ERROR)
			return (ERROR);
		color = (color << 8) + number;
		ptr += len + 1 * (len != 2);
		i++;
	}
	if (*ptr != '\0')
		return (ERROR);
	return (color);
}

static void	parse_color(t_game *game, t_list *node)
{
	char	*ptr;
	int		color;
	char	**rgb;

	ptr = node->content + 2 + ft_strspn(node->content + 2, " ");
	color = get_color(game, ptr);
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
