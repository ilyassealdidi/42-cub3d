/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:38:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/10 15:50:56 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

// int		parse_settings(t_game *game)
// {
// 	char	*line;
// 	int		status;
// 	t_list	*list;

// 	list = game->file.lines;
// 	status = SUCCESS;
// 	while (!are_settings_set(&game->settings) && isset(list))
// 	{
// 		line = list->content;
// 		if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
// 			status = parse_color(game, line);
// 		else if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0
// 			|| ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
// 			status = parse_texture(game, line);
// 		else if (*line == '\n' && list->previous != NULL)
// 			;
// 		else
// 			map_error(game, line, "Invalid identifier\n");
// 		if (status != SUCCESS)
// 			break ;
// 		list = list->next;
// 	}
// 	if (status == SUCCESS && !are_settings_set(&game->settings))
// 		map_error(game, line, "Missing Informations\n");
// 	game->map.map = list;
// 	return (status);
// }

// bool isvalidprevnext(t_list *list, int i)
// {
// 	char	*prev;
// 	char	*next;

// 	prev = NULL;
// 	next = NULL;
// 	if (list->previous)
// 		prev = list->previous->content;
// 	if (list->next)
// 		next = list->next->content;
// 	if (prev == NULL || next == NULL)
// 		return (false);
// 	if (i < ft_strlen(prev) && i < ft_strlen(next))
// 	{
// 		if (prev[i] == ' ' || next[i] == ' ')
// 			return (false);	
// 	}
// 	else
// 		return (false);
// 	return (true);
// }

// bool	is_valid_line(t_game *game, t_list *list, char *line)
// {
// 	int		i;

// 	if (list->next != NULL)
// 		line[ft_strlen(line) - 1] = '\0';
// 	if (ft_strspn(line, " 10NSEW") != ft_strlen(line))
// 		return (false);
// 	if ((ft_strchr(" 1", ((char *)(list->previous->content))[0]) == NULL || list->next == NULL)
// 		&& ft_strspn(line, " 1") != ft_strlen(line))
// 		return (false);
// 	if (list->next != NULL && list->previous != NULL)
// 	{
// 		i = 0;
// 		while (line[i])
// 		{
// 			if (ft_strchr("NSEW0", line[i]))
// 			{
// 				if (i == 0 || i == ft_strlen(line) - 1
// 					|| line[i - 1] == ' ' || line[i + 1] == ' '
// 					|| line[i + 1] == '\0' || !isvalidprevnext(list, i))
// 					return (false);
// 			}
// 			if (ft_strchr("NSEW", line[i]))
// 			{
// 				if (game->player.x != 0)
// 					return (false);
// 				game->player.x = i + 1;
// 				game->player.y = get_line_number(game->map.map, line);
// 			}
// 			i++;
// 		}
// 	}
// 	return (true);
// }

// int	set_map(t_game *game, t_list *list)
// {
// 	int		i;
// 	char	*line;

// 	i = 0;
// 	game->map.height = ft_lstsize(list);
// 	if (game->map.height < 3)
// 		map_error(game, list->content, "Invalid map\n");
// 	while (list != NULL)
// 	{
// 		line = list->content;
// 		if (!is_valid_line(game, list, line))
// 			map_error(game, line, "Invalid map\n");
// 		list = list->next;
// 		i++;
// 	}
// 	return (SUCCESS);
// }

void	set_game_file(t_game *game, char *filename)
{
	int		fd;
	int		len;
 
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		exit_with_error(EFILE);
	game->file.name = filename;
	fd = open_file(filename);
	if (fd == -1)
		perr(filename);
	game->file.lines = read_file(fd);
	close(fd);
	if (errno != 0)
		exit_with_error(strerror(errno));
}

void	parse_settings(t_game *game)
{
	t_list	*ptr;
	void (*func[2])(t_game *, t_list **);

	func[0] = parse_colors;
	func[1] = parse_textures;
	ptr = game->file.lines;
	if (is_color(game->file.lines->content) || is_texture(game->file.lines->content))
	{
		func[is_texture(game->file.lines->content)](game, &ptr);
		func[is_color(game->file.lines->content)](game, &ptr);
	}
	else
		map_error(game, ptr->content, "Invalid identifier\n");
}

void	game_init(t_game *game, char *filename)
{
	set_defaults(game);
	set_game_file(game, filename);
	if (game->file.lines == NULL)
		exit_with_error(EEMPTY);
	parse_settings(game);
	// parse_map(game);
	ft_lstclear(&game->file.lines, free);
}
