/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:26:12 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/11 20:58:44 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>


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
	return (head);
}
