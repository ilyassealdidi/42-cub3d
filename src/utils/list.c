/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:07:42 by ialdidi           #+#    #+#             */
/*   Updated: 2024/10/04 19:30:15 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int append_item(t_list **lines, void *line)
{
	t_list  *new;

	new = ft_lstnew(line);
	if (!isset(new))
		return (FAILURE);
	ft_lstadd_back(lines, new);
	return (SUCCESS);
}
