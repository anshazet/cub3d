/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:11:06 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/06 16:16:14 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_draw_mini_map(t_data *data)
{
	int	y;
	int	x;
	int	color;
	int	mini_map_x;
	int	mini_map_y;

	y = 0;
	while (y < data->map_max_y)
	{
		x = 0;
		while (x < data->map_max_x)
		{
			mini_map_x = X_OFFSET + (x * MINI_MAP_SCALE);
			mini_map_y = Y_OFFSET + (y * MINI_MAP_SCALE);
			if (data->map[y][x] == '1')
			{
				color = 0xFFFFFF; // White for walls
			}
			else if (data->map[y][x] == '0' || data->map[y][x] == 'N' \
					|| data->map[y][x] == 'S' || data->map[y][x] == 'E' \
						|| data->map[y][x] == 'W')
			{
				color = 0x000000; // Black for empty space
			}
			else
			{
				x++;
				continue;
			}
			// Draw the map element
			int dy = 0;
			while (dy < MINI_MAP_SCALE)
			{
				int dx = 0;
				while (dx < MINI_MAP_SCALE)
				{
					img_pix_put(&data->img, mini_map_x + dx, mini_map_y + dy, color);
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}
	ft_draw_mini_player(data);

}

void ft_draw_mini_player(t_data *data)
{
	float	py;
	float	px;

	py = 0;
		// Draw the player on the mini-map
	int playerMapX = X_OFFSET + (int)(data->player->pos.x * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4; // Center the square on the player
	int playerMapY = Y_OFFSET + (int)(data->player->pos.y * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4; // Center the square on the player
	float playerSize = MINI_MAP_SCALE / 2;														 // Size of the square representing the player

	while (py < playerSize)
	{
		px = 0;
		while (px < playerSize)
		{
			img_pix_put(&data->img, playerMapX + px - playerSize / 2, playerMapY + py - playerSize / 2, 0xFF0000); // Red square for the player
			px++;
		}
		py++;
	}
	// Draw the direction indicator
	float directionSize = playerSize * 2; // Size of the directional indicator
	float angle = ft_deg_to_rad(data->player->angle + 90); // TO FIX
	int dx = (int)(cosf(angle) * directionSize);
	int dy = (int)(sinf(angle) * directionSize);

	// Draw a line for the direction
	int i = 0;
	while (i < directionSize)
	{
		float directionX = playerMapX + (dx * i) / directionSize;
		float directionY = playerMapY + (dy * i) / directionSize;
		if (i >= playerSize / 2)
		{															   // Start drawing after half the player size
			img_pix_put(&data->img, directionX, directionY, 0xFF0000); // Yellow line for direction
		}
		i++;
	}
}

