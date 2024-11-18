/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:19:39 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/18 15:40:11 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define USAGE "Usage: ./cub3D [map.cub]"

# define EOPEN "Can't open file"
# define EEMPTY "Empty file"
# define ESEP "Expected empty line"
# define EFILE "Allowed files: *.cub"
# define EMAP "Invalid map"
# define ECOLOR "Invalid color"
# define ETEXSET "Texture already set"
# define ECOLORSET "Color already set"
# define EIDENTIFIER "Invalid identifier"
# define EINVALIDMAP "Invalid map"
# define EMISSTEX "Missing texture"
# define EMISSCOLOR "Missing color"
# define EMISSMAP "Missing map"
# define EMISSINFO "Missing informations"

# define ERROR -1
# define FAILURE 0
# define SUCCESS 1

# define RED "\033[1;31m"
# define YELLOW "\033[0;33m"
# define GREEN "\033[0;32m"
# define BLUE "\033[0;34m"
# define CYAN "\033[0;36m"
# define MAGENTA "\033[0;35m"
# define BRIGHT_RED "\033[0;91m"
# define BRIGHT_GRAY "\033[1;90m"
# define BRIGHT_YELLOW "\033[0;93m"
# define BRIGHT_BLUE "\033[0;94m"
# define BRIGHT_MAGENTA "\033[0;95m"

# define SPACE "\033[1;95m·\033[m"
# define ERROR_HEAD "\033[1;31m\nError\n\n\033[m"

# define RESET "\033[m"

# define WIDTH 1200
# define HEIGHT 720
# define TILE_SIZE 30
# define FOV 60
# define SPEED 1

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

typedef struct s_point
{
	double		x;
	double		y;
}	t_point;

typedef struct s_map
{
	char		**map;
	int			width;
	int			height;
}	t_map;

typedef struct s_player
{
	t_point		pos;
	double		dir;
	// double	plane;
}	t_player;

typedef struct s_file
{
	char	*name;
	t_list	*lines;
}	t_file;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
}	t_mlx;

typedef struct s_game
{
	t_mlx		mlx;
	t_file		file;
	t_settings	settings;
	t_map		map;
	t_player	player;
	t_list		*current_line;
}	t_game;

#endif

// l7uub : 1,140
// Ana : 1,328