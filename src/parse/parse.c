/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:38:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/10/08 19:07:40 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	get_line_number(t_list *list, char *line)
{
	int		i;

	i = 1;
	while (list->content != line)
	{
		list = list->next;
		i++;
	}
	return (i);
}

int	open_file(char *filename)
{
	int		fd;
	int		len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		exit_with_error(EFILE);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_with_error(NULL);
	return (fd);
}

int	read_lines(t_list **lines, int fd)
{
	char	*line;

	*lines = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (append_item(lines, line) == FAILURE)
		{
			free(line);
			ft_lstclear(lines, free);
			return (FAILURE);
		}
	}
	return (SUCCESS);
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

int	parse_texture(t_game *game, char *line)
{
	char	*texture;
	int		fd;
	int		i;

	i = 2;
	while (line[i] == ' ')
		i++;
	line[ft_strlen(line) - 1] = '\0';
	texture = ft_strdup(line + i);
	if (texture == NULL)
		return (FAILURE);
	if (*line == 'N' && game->settings.north == NULL)
		game->settings.north = texture;
	else if (*line == 'S' && game->settings.south == NULL)
		game->settings.south = texture;
	else if (*line == 'W' && game->settings.west == NULL)
		game->settings.west = texture;
	else if (*line == 'E' && game->settings.east == NULL)
		game->settings.east = texture;
	else
	{
		free(texture);
		return (print_map_error(game, line, "Texture already set"), ERROR);
	}
	fd = open(texture, O_RDONLY);
	if (fd == -1)
	{
		free(texture);
		return (print_map_error(game, line, "Cannot open the file"), ERROR);
	}
	return (SUCCESS);
}

int	parse_settings(t_game *game)
{
	char	*line;
	int		status;
	t_list	*list;

	list = game->file_lines;
	status = SUCCESS;
	while (!are_settings_set(&game->settings) && isset(list))
	{
		line = list->content;
		if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
			status = parse_color(game, line);
		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
			status = parse_texture(game, line);
		else if (*line == '\n' && list->previous != NULL)
			;
		else
			return (print_map_error(game, line, "Invalid identifier\n"), ERROR);
		if (status != SUCCESS)
			break ;
		list = list->next;
	}
	if (status == SUCCESS && !are_settings_set(&game->settings))
		return (print_map_error(game, line, "Missing Informations\n"), ERROR);
	game->map.map = list;
	return (status);
}

bool isvalidprevnext(t_list *list, int i)
{
	char	*prev;
	char	*next;

	prev = NULL;
	next = NULL;
	if (list->previous)
		prev = list->previous->content;
	if (list->next)
		next = list->next->content;
	if (prev == NULL || next == NULL)
		return (false);
	if (i < ft_strlen(prev) && i < ft_strlen(next))
	{
		if (prev[i] == ' ' || next[i] == ' ')
			return (false);	
	}
	else
		return (false);
	return (true);
}

bool	is_valid_line(t_game *game, t_list *list, char *line)
{
	int		i;

	if (list->next != NULL)
		line[ft_strlen(line) - 1] = '\0';
	if (ft_strspn(line, " 10NSEW") != ft_strlen(line))
		return (false);
	if ((ft_strchr(" 1", ((char *)(list->previous->content))[0]) == NULL || list->next == NULL)
		&& ft_strspn(line, " 1") != ft_strlen(line))
		return (false); //kanmooooot 3lik azine dyali
	if (list->next != NULL && list->previous != NULL)
	{
		i = 0;
		while (line[i])
		{
			if (ft_strchr("NSEW0", line[i]))
			{
				if (i == 0 || i == ft_strlen(line) - 1
					|| line[i - 1] == ' ' || line[i + 1] == ' '
					|| line[i + 1] == '\0' || !isvalidprevnext(list, i))
					return (false);
			}
			if (ft_strchr("NSEW", line[i]))
			{
				if (game->player.x != 0)
					return (false);
				game->player.x = i + 1;
				game->player.y = get_line_number(game->map.map, line);
			}
			i++;
		}
	}
	return (true);
}

int	set_map(t_game *game, t_list *list)
{
	int		i;
	char	*line;

	i = 0;
	game->map.height = ft_lstsize(list);
	if (game->map.height < 3)
		return (print_map_error(game, list->content, "Invalid map\n"), ERROR);
	while (list != NULL)
	{
		line = list->content;
		if (!is_valid_line(game, list, line))
			return (print_map_error(game, line, "Invalid map\n"), ERROR);
		list = list->next;
		i++;
	}
	return (SUCCESS);
}

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

int	game_init(t_game *game, char *file)
{
	int 	fd;
	int 	status;

	set_defaults(game);
	fd = open_file(file);
	game->map.filename = file;
	status = read_lines(&game->file_lines, fd);
	if (status == SUCCESS)
	{
		status = parse_settings(game);
		if (status == SUCCESS)
			status = parse_map(game);
	}
	close(fd);
	ft_lstclear(&game->file_lines, free);
	return (status);
}
