/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:07:37 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/07 20:42:43 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <libft.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <types.h>

/*		Parse				*/
void	set_defaults(t_game *game);
bool	are_settings_set(t_settings *settings);
int		game_init(t_game *game, char *file);

/*		Error handling		*/
void	perr(char *str);
void    exit_with_error(char *str);
void	map_error(t_game *game, char *line, char *error);

/*		Utils				*/
bool	isset(void *ptr);
bool	is_color(char *line);
bool	is_texture(char *line);
bool	is_color_set(t_settings *settings);
bool	is_texture_set(t_settings *settings);

/*		Linked list			*/
int     append_item(t_list **lines, void *line);

/*		File utils			*/
t_list	*read_file(int fd);
int		open_file(char *filename);

#endif
