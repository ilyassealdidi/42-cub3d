/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:38:35 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/30 01:35:20 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	set_defaults(t_game *game)
{
	errno = 0;
	ft_memset(game, 0, sizeof(t_game));
	game->settings.floor = -1;
	game->settings.ceiling = -1;
}

static void	set_game_file(t_game *game, char *filename)
{
	int		fd;
	int		len;
 
	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		exit_with_error(game, EFILE);
	game->file.name = ft_strdup(filename);
	if (game->file.name == NULL)
		exit_with_error(game, NULL);
	fd = open(game->file.name, O_RDONLY);
	if (fd == -1)
		file_error(game, game->file.name);
	game->file.lines = read_file(fd);
	close(fd);
	if (errno != 0)
		exit_with_error(game, NULL);
	if (game->file.lines == NULL)
		exit_with_error(game, EEMPTY);
}

static void	parse_settings(t_game *game, t_list **ptr)
{
	if (is_color(game->file.lines->content) || is_texture(game->file.lines->content))
		parse_colors_textures(game, ptr);
	else
		map_error(game, *ptr, EIDENTIFIER);
}

void	game_init(t_game *game, char *filename)
{
	t_list	*ptr;

	set_defaults(game);
	set_game_file(game, filename);
	ptr = game->file.lines;
	parse_settings(game, &ptr);
	parse_map(game, &ptr);
	ft_lstclear(&game->file.lines, free);
}
