/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:26:12 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/06 12:11:16 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int	open_file(char *filename)
{
	int		len;

	len = ft_strlen(filename);
	if (len < 4 || ft_strncmp(filename + len - 4, ".cub", 4))
		return (-1);
	return (open(filename, O_RDONLY));
}

t_list	*read_file(int fd)
{
	char	*line;
	t_list	*head;

	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (ft_lstappend(&head, line) == FAILURE)
		{
			free(line);
			ft_lstclear(&head, free);
			return (NULL);
		}
	}
	return (head);
}
