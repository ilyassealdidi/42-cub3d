/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:42:27 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/26 21:19:35 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void    exit_with_error(t_game *game, char *error)
{
	ft_dprintf(2, ERROR_HEAD);
	if (error)
		ft_putendl_fd(error, 2);
	else
		perror(NULL);
	ft_putchar_fd('\n', 2);
	clean_exit(game, 1);
}

int	get_line_number(t_list *list)
{
	int		i;

	i = 0;
	while (list)
	{
		list = list->previous;
		i++;
	}
	return (i);
}

void	map_error(t_game *game, t_list *node, char *error)
{
	int		number;
	char	*line;

	line = node->content;
	number = get_line_number(node);
	ft_dprintf(2, ERROR_HEAD);
	ft_dprintf(2, "%s ", error);
	ft_dprintf(2, "at: %s:%d\n", game->file.name, number);
	if (ft_strlen(line))
	{
		ft_dprintf(2, "\n");
		ft_dprintf(2, BRIGHT_GRAY"#%d "RESET"", number);
		while (*line)
		{
			if (*line == ' ')
				ft_dprintf(2, SPACE);
			else
				ft_dprintf(2, "%c", *line);
			line++;
		}
		ft_dprintf(2, "\n");
	}
	ft_dprintf(2, "\n");
	clean_exit(game, 1);
}
