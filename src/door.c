/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:54:19 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/11 10:35:23 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// nitialize facing_door to 0 in ft_put_player function

void ft_interact_door(t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = (int)(data->player->pos.x + cosf(ft_deg_to_rad(data->player->angle - 90.0f)) * 1.0f);
	map_y = (int)(data->player->pos.y + -sinf(ft_deg_to_rad(data->player->angle - 90.0f)) * 1.0f);
	printf("map_x%d | map_y%d\nMap _char%c\n", map_x, map_y, data->map[map_y][map_x]);
	// Check if facing a door
	if (data->map[map_y][map_x] == 'D')
	{
		//data->player->facing_door = 1;

		// Open or close the door
		if (data->map[map_y][map_x] == 'D')
		{
			data->map[map_y][map_x] = '0'; // Change to open space
	 	}
     }
	// 	else
	// 	{
	// 		data->map[map_y][map_x] = 'D'; // Change back to door
	// 	}
	// }
	// else
	// {
	// 	//data->player->facing_door = 0;
	// }
}
/* put 0 ou 1
void ft_raycast(t_data *data)
{
	// ... existing raycasting code ...

	// Check if the ray hit a door
	if (data->map[data->rcast->map.y][data->rcast->map.x] == 'D')
	{
		data->player->facing_door = true;
		data->player->door_x = data->rcast->map.x;
		data->player->door_y = data->rcast->map.y;
	}
	else
	{
		data->player->facing_door = false;
	}

	// ... rest of raycasting code ...
}
*/
