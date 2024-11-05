/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 17:42:27 by ialdidi           #+#    #+#             */
/*   Updated: 2024/10/05 20:12:32 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void    exit_with_error(char *str)
{
    // ft_dprintf(2, "Error\n");
    ft_putstr_fd("Error\n", 2);
    if (isset(str))
    {
        ft_dprintf(2, "%s", str);
        exit(ERROR);
    }
    perror(NULL);
    exit(FAILURE);
}

void    perr(char *str)
{
    ft_dprintf(2, "Error\n");
    if (isset(str))
        ft_dprintf(2, "%s", str);
    else
        perror(NULL);
}
