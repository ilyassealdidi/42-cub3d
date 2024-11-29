/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:29:06 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/29 00:03:00 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static int	set_map_array(t_map *map, t_list *list)
{
	int		i;

	map->map = ft_calloc(sizeof(char *), (map->rows + 1));
	if (map->map == NULL)
		return (FAILURE);
	i = 0;
	while (i < map->rows)
	{
		map->map[i] = ft_calloc(sizeof(char), (map->columns + 1));
		if (map->map[i] == NULL)
			return (free_array(map->map), FAILURE);
		ft_memcpy(map->map[i], list->content, ft_strlen(list->content));
		list = list->next;
		i++;
	}
	return (SUCCESS);
}

static bool	is_valid_map(t_map *map)
{
	int		i;
	int		j;

	if (ft_strpbrk(map->map[0], "0NSEW") != NULL
		|| ft_strpbrk(map->map[map->rows - 1], "0NSEW") != NULL)
		return (false);
	i = 1;
	while (i < map->rows - 1)
	{
		j = 0;
		while (map->map[i][j])
		{
			if (ft_strchr("NSEW0", map->map[i][j])
				&& (j == 0 || j == map->columns - 1
				|| ft_strchr(" ", map->map[i][j - 1])
				|| ft_strchr(" ", map->map[i][j + 1])
				|| ft_strchr(" ", map->map[i - 1][j])
				|| ft_strchr(" ", map->map[i + 1][j])))
					return (false);
			j++;
		}
		i++;
	}
	return (true);
}

static void	set_map(t_game *game, t_list *list)
{
	char	*line;
	t_list	*tmp;
	int		len;

	tmp = list;
	game->map.rows = ft_lstsize(list);
	if (game->map.rows < 3)
		exit_with_error(game, EINVALIDMAP);
	while (list != NULL)
	{
		line = list->content;
		len = ft_strlen(line);
		if (len == 0 || ft_strspn(line, " 10NSEW") != ft_strlen(line))
			map_error(game, list, EINVALIDMAP);
		if (len > game->map.columns)
			game->map.columns = len;
		list = list->next;
	}
	if (set_map_array(&game->map, tmp) == FAILURE)
		exit_with_error(game, NULL);
}

static void	set_player_pos(t_game *game)
{
	int		i;
	char	*ptr;

	i = -1;
	while (game->map.map[++i])
	{
		ptr = ft_strpbrk(game->map.map[i], "NSEW");
		if (ptr != NULL)
		{
			if (game->player.pos.x != 0)
				exit_with_error(game, EPLAYERSET);
			if (*ptr == 'N')
				game->player.dir = 3 * M_PI_2;
			else if (*ptr == 'S')
				game->player.dir = M_PI_2;
			else if (*ptr == 'W')
				game->player.dir = M_PI;
			else if (*ptr == 'E')
				game->player.dir = 0;
			set_point(&game->player.pos,
				(ptr - game->map.map[i]) * TILE_SIZE + TILE_SIZE / 2,
				i * TILE_SIZE + TILE_SIZE / 2);
		}
	}
}

void	parse_map(t_game *game, t_list **list)
{
	if (*list == NULL)
		exit_with_error(game, EMISSMAP);
	set_map(game, *list);
	set_player_pos(game);
	if (game->player.pos.x == 0)
		exit_with_error(game, EPLAYER);
	if (!is_valid_map(&game->map))
		exit_with_error(game, EINVALIDMAP);
}
