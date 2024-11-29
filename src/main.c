/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ialdidi <ialdidi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 19:06:39 by ialdidi           #+#    #+#             */
/*   Updated: 2024/11/28 23:32:24 by ialdidi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub.h>

void leaks() {system("leaks cub3D");} //! remove this line before

int main(int ac, char **av)
{
    t_game	game;

	atexit(leaks); //! remove this line before
    if (ac != 2)
	{
		ft_putstr_fd(USAGE, 2);
        return (EXIT_FAILURE);
	}
    game_init(&game, av[1]);
    rungame(&game);
	clean_exit(&game, EXIT_SUCCESS);
}
