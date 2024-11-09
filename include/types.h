/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:19:39 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/09 19:02:45 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define USAGE "Usage: ./cub3D [map.cub]\n"

# define EOPEN "Can't open file\n"
# define EEMPTY "Empty file\n"
# define ECLOSE "Can't close file\n"
# define EFILE "Allowed files: *.cub\n"
# define EMAP "Invalid map\n"
# define ECOLOR "Invalid color\n"

# define ERROR -1
# define FAILURE 0
# define SUCCESS 1

# define RED "\033[1;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define MAGENTA "\033[0;35m"
# define BRIGHT_RED "\033[1;91m"
# define BRIGHT_GREEN "\033[0;92m"
# define BRIGHT_YELLOW "\033[0;93m"
# define BRIGHT_BLUE "\033[0;94m"
# define BRIGHT_MAGENTA "\033[0;95m"
# define LINE "\033[0;90;100m"

# define SPACE "\033[1;95m·\033[m"
# define NEWLINE "\033[1;95m↵\033[m"

# define RESET "\033[m"

typedef unsigned char	t_byte;
typedef int				t_color;

typedef struct s_settings
{
	char		*north;
	char		*south;
	char		*west;
	char		*east;
	t_color		floor;
	t_color		ceiling;
}	t_settings;

typedef struct s_map
{
	t_list		*map;
	int			width;
	int			height;
}	t_map;

typedef struct s_player
{
	double	x;
	double	y;
	// double	dir;
	// double	plane;
}	t_player;

typedef struct s_file
{
	char	*name;
	t_list	*lines;
}	t_file;

// typedef struct s_line
// {
// 	char	*content;
// 	int		number;
// 	int		length;
// }	t_line;

typedef struct s_game
{
	// void		*mlx;
	t_file		file;
	t_settings	settings;
	t_map		map;
	t_player	player;
	t_list		*current_line;
}	t_game;

#endif

// l7uub : 1,140
// Ana : 1,328