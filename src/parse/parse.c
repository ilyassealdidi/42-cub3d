/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:38:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/12 13:37:09 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	set_game_file(t_game *game, char *filename)
{
	int		fd;
	int		len;
 
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		exit_with_error(game, EFILE);
	game->file.name = ft_strdup(filename);
	if (game->file.name == NULL)
		exit_with_error(game, NULL);
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		file_error(game, filename);
	game->file.lines = read_file(fd);
	close(fd);
	if (errno != 0)
		exit_with_error(game, NULL);
}

void	parse_settings(t_game *game, t_list **ptr)
{
	void (*func[2])(t_game *, t_list **);

	func[0] = parse_colors;
	func[1] = parse_textures;
	if (is_color(game->file.lines->content) || is_texture(game->file.lines->content))
	{
		func[is_texture(game->file.lines->content)](game, ptr);
		if (*ptr == NULL)
			exit_with_error(game, EMISSINFO);
		if (ft_strlen((*ptr)->content) != 0)
			map_error(game, *ptr, ESEP);
		while (*ptr && ft_strlen((*ptr)->content) == 0)
			*ptr = (*ptr)->next;
		func[is_color(game->file.lines->content)](game, ptr);
	}
	else
		map_error(game, *ptr, EIDENTIFIER);
}

void	game_init(t_game *game, char *filename)
{
	t_list	*ptr;

	set_defaults(game);
	set_game_file(game, filename);
	if (game->file.lines == NULL)
		exit_with_error(game, EEMPTY);
	ptr = game->file.lines;
	parse_settings(game, &ptr);
	parse_map(game, &ptr);
	ft_lstclear(&game->file.lines, free);
}
