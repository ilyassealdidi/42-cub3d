/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:07:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/27 22:47:19 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <MLX42.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <types.h>

/*		Parse				*/
void	set_defaults(t_game *game);
void	parse_colors_textures(t_game *game, t_list **list);
void	parse_map(t_game *game, t_list **list);
void	game_init(t_game *game, char *filename);


/*		Graphics			*/
void	render_map(t_game *game);
void	move_player(void *ptr);
void	rungame(t_game *game);

/*		Player utils	*/
bool	is_face_up(double dir);
bool	is_face_down(double dir);
bool	is_face_left(double dir);
bool	is_face_right(double dir);

/*		Error handling		*/
void    exit_with_error(t_game *game, char *str);
void	map_error(t_game *game, t_list *node, char *error);

/*		Intersection		*/
double	get_distance(t_game *game, double rayangle);

/*		Utils				*/
void	normalize_angle(double *angle);
void	free_array(char **array);
void	clean_exit(t_game *game, int status);
bool	isset(void *ptr);
bool	is_color(char *line);
bool	is_texture(char *line);
bool	is_color_set(t_settings *settings);
bool	is_texture_set(t_settings *settings);
int		num_char(char *ptr, char c);

/*		Linked list			*/
int 	ft_lstappend(t_list **lines, void *content);

/*		File utils			*/
t_list	*read_file(int fd);
void	file_error(t_game *game, char *filename);


#endif
