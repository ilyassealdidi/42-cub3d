/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:06:39 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/10 12:20:46 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int main(int ac, char **av)
{
    t_game  game;

    if (ac != 2)
        return (ft_putstr_fd(USAGE, 2), 1);
    game_init(&game, av[1]);
    // rungame(&game);
}
