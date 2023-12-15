/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brandebr <brandebr@student.42barcelona.co  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:26:44 by brandebr          #+#    #+#             */
/*   Updated: 2023/12/15 17:03:22 by brandebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int		player_position(t_map *game)
{
		game->player.x = 0;
		game->player.y = 0;
		while (game->player.y <= game->height && game->player.x <= game->width)
		{
				if (game->map[game->player.y][game->player.x] == 'P')
						return (0);
				game->player.x++;
				if (game->player.x == game->width)
				{
						game->player.x = 0;
						game->player.y++;
				}
		}
		return (0);	
}

int		map_check(t_map *game)
{
		if (ft_outer_limits(game) == -1)
		{
				ft_free_map(game);
				write(2, "ERROR\nThe Board is not correctly defined\n", 41);
				exit (-1);
		}
		if ((ft_collectibles(game) == -1) || (exit_player_check(game) == -1))
		{
				ft_free_map(game);
				write(2, "ERROR\nWrong Players, exits or collectibles", 43);
				exit (-1);
		}
		ft_rectangle_check(game);
		player_position(game);
		flood_map(game, game->player.x, game->player.y);
		if (game->coins_cpy != 0)
		{
				write (2, "Error\nNo valid path between player and exit", 44);
				exit (-1);
		}
		return (0);
}

int		main(int argc, char **argv)
{
		t_map	game;

		game.count = 0;
		parse_it(argc, argv);
		ft_read_map(argv, &game);
		ft_measures(&game);
		game.map_cpy = cpy_map(&game);
		map_check(&game);
//		if (game.exit != 0)
//		{
//				write (2, "Error\nThere's not a path between the p and the exit\n", 57);
//				exit (-1);
//		}
		write(1, "Hi there Ford", 13);
		ft_printf(" 🐬 thanks for all  the fish 🖖");
		exit (0);
}
