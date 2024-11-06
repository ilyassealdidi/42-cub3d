/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:42:27 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/06 13:48:03 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void    exit_with_error(char *error)
{
	ft_putstr_fd("Error\n", 2);
	ft_dprintf(2, "%s", error);
	exit(FAILURE);
}

void    perr(char *str)
{
    ft_dprintf(2, "Error\n");
	perror(str);
}

void	print_map_error(t_game *game, char *line, char *error)
{
	int	line_number;

	line_number = get_line_number(game->file_lines, line);
	ft_dprintf(2, RED"Error\n\n"RESET);
	ft_dprintf(2, "\t%s", error);
	ft_dprintf(2, "\n\tline: %s:%d\n", game->map.filename, line_number);
	ft_dprintf(2, RED"\n\t|"RESET" #%d ", line_number);
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
}