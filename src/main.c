/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:14:02 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/28 18:07:28 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	else
		printf("Welcome to cub3d\n");
	data = ft_parse_map(av[1]);
	if (!data)
	{
		printf("error\n");
		return (0);
	}
	printf("[DEBUG] Textures* :%p, %p, %p ,%p\nColors Hex : %u, %u\n", data->textures->no, data->textures->so, data->textures->ea, data->textures->we, data->textures->floor, data->textures->ceiling);
	data->win = mlx_new_window(data->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	mlx_hook(data->win, 17, 0L, ft_close_button, data);
	mlx_loop(data->mlx);
	ft_free_all(data);
	return (0);
}
