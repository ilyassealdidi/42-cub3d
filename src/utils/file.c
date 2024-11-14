/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:26:12 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/14 13:28:34 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void	file_error(t_game *game, char *filename)
{
	ft_printf(RED"Error\n"RESET);
	perror(filename);
	clean_exit(game, EXIT_FAILURE);
}

void	remove_newline(t_list *list)
{
	while (list->next)
	{
		ft_strchr(list->content, '\n')[0] = '\0';
		list = list->next;
	}
}

t_list	*read_file(int fd)
{
	char	*line;
	t_list	*head;

	head = NULL;
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
	if (head != NULL)
		remove_newline(head);
	return (head);
}
