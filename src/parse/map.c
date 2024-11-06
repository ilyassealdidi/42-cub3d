/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 12:29:06 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/06 12:29:13 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	parse_map(t_game *game)
{
	t_list	*list;
	char	*line;
	int		i;
	int		status;

	list = game->map.map;
	i = 0;
	while (list != NULL)
	{
		line = list->content;
		if (*line != '\n')
			break ;
		list = list->next;
	}
	if (list == NULL)
		return (print_map_error(game, line, "No map found\n"), ERROR);
	status = set_map(game, list);
	if (status != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
