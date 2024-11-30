/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:13 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/30 14:06:41 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int num_char(char *ptr, char c)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (ptr[i])
	{
		if (ptr[i] == c)
			count++;
		i++;
	}
	return (count);
}

bool	is_color(char *line)
{
	if (line == NULL)
		return (false);
	return (ft_strncmp(line, "F ", 2) == 0
		|| ft_strncmp(line, "C ", 2) == 0);
}

bool	is_texture(char *line)
{
	if (line == NULL)
		return (false);
	return (ft_strncmp(line, "NO ", 3) == 0
		|| ft_strncmp(line, "SO ", 3) == 0
		|| ft_strncmp(line, "WE ", 3) == 0
		|| ft_strncmp(line, "EA ", 3) == 0);
}

bool is_color_set(t_settings *settings)
{
	return (settings->floor != -1
		&& settings->ceiling != -1);
}

bool is_texture_set(t_settings *settings)
{
	return (settings->textures[NORTH] != NULL
		&& settings->textures[SOUTH] != NULL
		&& settings->textures[EAST] != NULL
		&& settings->textures[WEST] != NULL);
}
