
// void	parse_textures(t_game *game, char *line)
// {
// 	char	*texture;
// 	int		fd;
// 	int		i;

// 	i = 2;
// 	while (line[i] == ' ')
// 		i++;
// 	line[ft_strlen(line) - 1] = '\0';
// 	texture = ft_strdup(line + i);
// 	if (texture == NULL)
// 		clean_exit(game, EXIT_FAILURE);
// 	if (*line == 'N' && game->settings.north == NULL)
// 		game->settings.north = texture;
// 	else if (*line == 'S' && game->settings.south == NULL)
// 		game->settings.south = texture;
// 	else if (*line == 'W' && game->settings.west == NULL)
// 		game->settings.west = texture;
// 	else if (*line == 'E' && game->settings.east == NULL)
// 		game->settings.east = texture;
// 	else
// 	{
// 		free(texture);
// 		map_error(game, line, "Texture already set");
// 	}
// 	fd = open(texture, O_RDONLY);
// 	if (fd == -1)
// 	{
// 		free(texture);
// 		map_error(game, line, "Cannot open the file");
// 	}
// }