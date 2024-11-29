/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:26:12 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/28 23:50:09 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

static void	remove_newline(t_list *list)
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
	t_list	*new;

	head = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		new = ft_lstnew(line);
		if (new == NULL)
		{
			free(line);
			ft_lstclear(&head, free);
			return (NULL);
		}
		ft_lstadd_back(&head, new);
	}
	if (head != NULL)
		remove_newline(head);
	return (head);
}
