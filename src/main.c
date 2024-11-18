/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmalyana <gmalyana@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:06:39 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/18 21:30:29 by gmalyana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

int main(int ac, char **av)
{
    t_game	game;

    if (ac != 2)
	{
		ft_putstr_fd(USAGE, 2);
        return (EXIT_FAILURE);
	}
    game_init(&game, av[1]);
    rungame(&game);
}
