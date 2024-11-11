/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:42:27 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/11 22:53:40 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void    exit_with_error(t_game *game, char *error)
{
	ft_putstr_fd("Error\n", 2);
	if (error)
		ft_putendl_fd(error, 2);
	else
		perror(NULL);
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
	ft_dprintf(2, RED"Error\n\n"RESET);
	ft_dprintf(2, "\t%s", error);
	ft_dprintf(2, "\n\tline: %s:%d\n", game->file.name, number);
	ft_dprintf(2, RED"\n\t|"RESET" #%d ", number);
	while (*line)
	{
		if (*line == ' ')
			ft_dprintf(2, SPACE);
		else if (*line == '\n')
			ft_dprintf(2, NEWLINE);
		else
			ft_dprintf(2, "%c", *line);
		line++;
	}
	ft_dprintf(2, "\n\n");
	ft_dprintf(2, "\tSpaces are presented with a `"SPACE"`\n");
	ft_dprintf(2, "\tNewlines are presented with a `"NEWLINE"`\n\n");
	clean_exit(game, 1);
}
