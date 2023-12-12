/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:11:06 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/12 10:16:04 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_element(t_data *data, int mini_map_x, \
									int mini_map_y, int color)
{
	int	dy;
	int	dx;

	dy = 0;
	while (dy < MINI_MAP_SCALE)
	{
		dx = 0;
		while (dx < MINI_MAP_SCALE)
		{
			img_pix_put(&data->img, mini_map_x + dx, mini_map_y + dy, color);
			dx++;
		}
		dy++;
	}
}

int	ft_put_color(char map_value)
{
	if (map_value == '1' || map_value == '2')
		return (0xFFFFFF);
	else if (map_value == 'D' || map_value == 'O')
		return (0x00FFFF);
	else if (map_value == '0' || map_value == 'N' || map_value == 'S' \
			|| map_value == 'E' || map_value == 'W')
		return (0x000000);
	return (-1);
}

int	ft_should_draw(int mini_map_x, int mini_map_y)
{
	return (!(mini_map_x + MINI_MAP_SCALE > SCREENWIDTH \
			|| mini_map_y + MINI_MAP_SCALE > SCREENHEIGHT));
}

void	ft_draw_mini_map(t_data *data)
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
			if (!ft_should_draw(mini_map_x, mini_map_y))
			{
				x++;
				continue ;
			}
			color = ft_put_color(data->map[y][x]);
			if (color == -1)
			{
				x++;
				continue ;
			}
			draw_map_element(data, mini_map_x, mini_map_y, color);
			x++;
		}
		y++;
	}
	ft_draw_mini_player(data);
}

static void	ft_draw_indicator(t_data *data)
{
	float player_size = MINI_MAP_SCALE / 2;
	int player_map_x = X_OFFSET + (int)(data->player->pos.x * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4;
	int player_map_y = Y_OFFSET + (int)(data->player->pos.y * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4;
	float direction_size = player_size * 2;
	float angle = ft_deg_to_rad(data->player->angle + 90);
	int dx = (int)(-cosf(angle) * direction_size);
	int dy = (int)(sinf(angle) * direction_size);
	int i;

	i = 0;
	while (i < direction_size)
	{
		int directionX = player_map_x + (dx * i) / direction_size;
		int directionY = player_map_y + (dy * i) / direction_size;
		if (i >= player_size / 2)
		{
			img_pix_put(&data->img, directionX, directionY, 0xFF0000);
		}
		i++;
	}
}

void ft_draw_mini_player(t_data *data)
{
	float	py;
	float	px;

	py = 0;
	int player_map_x = X_OFFSET + (int)(data->player->pos.x * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4;
	int player_map_y = Y_OFFSET + (int)(data->player->pos.y * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4;
	float player_size = MINI_MAP_SCALE / 2;

	while (py < player_size)
	{
		px = 0;
		while (px < player_size)
		{
			if (player_map_x + MINI_MAP_SCALE > SCREENWIDTH || player_map_y + MINI_MAP_SCALE > SCREENHEIGHT)
			{
				px++;
				return;
			}
			img_pix_put(&data->img, player_map_x + px - player_size / 2, player_map_y + py - player_size / 2, 0xFF0000); // Red square for the player
			px++;
		}
		py++;
	}
	ft_draw_indicator(data);
}
/*
void ft_draw_mini_player(t_data *data)
{
	float	py;
	float	px;

	py = 0;
		// Draw the player on the mini-map
	int player_map_x = X_OFFSET + (int)(data->player->pos.x * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4;
	int player_map_y = Y_OFFSET + (int)(data->player->pos.y * MINI_MAP_SCALE) - MINI_MAP_SCALE / 4;
	float player_size = MINI_MAP_SCALE / 2;

	while (py < player_size)
	{
		px = 0;
		while (px < player_size)
		{
			if (player_map_x + MINI_MAP_SCALE > SCREENWIDTH || player_map_y + MINI_MAP_SCALE > SCREENHEIGHT)
			{
				px++;
				return;
			}
			img_pix_put(&data->img, player_map_x + px - player_size / 2, player_map_y + py - player_size / 2, 0xFF0000); // Red square for the player
			px++;
		}
		py++;
	}
	// Draw the direction indicator
	float direction_size = player_size * 2; // Size of the directional indicator
	float angle = ft_deg_to_rad(data->player->angle + 90); // TO FIX
	int dx = (int)(-cosf(angle) * direction_size);
	int dy = (int)(sinf(angle) * direction_size);

	// Draw a line for the direction
	int i = 0;
	while (i < direction_size)
	{
		int directionX = player_map_x + (dx * i) / direction_size;
		int directionY = player_map_y + (dy * i) / direction_size;
		if (i >= player_size / 2)
		{															   // Start drawing after half the player size
			img_pix_put(&data->img, directionX, directionY, 0xFF0000); // Yellow line for direction
		}
		i++;
	}
}
*/
/*
void	ft_draw_mini_map(t_data *data)
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
			if (mini_map_x + MINI_MAP_SCALE > SCREENWIDTH \
			|| mini_map_y + MINI_MAP_SCALE > SCREENHEIGHT)
			{
				x++;
				continue;
			}
			if (data->map[y][x] == '1' || data->map[y][x] == '2' \
					|| data->map[y][x] == '3' || data->map[y][x] == '4' \
						|| data->map[y][x] == '5')
			{
				color = 0xFFFFFF;
			}
			else if (data->map[y][x] == 'D' || data->map[y][x] == 'O')
			{
				color = 0x00FFFF;
			}
			else if (data->map[y][x] == '0' || data->map[y][x] == 'N' \
					|| data->map[y][x] == 'S' || data->map[y][x] == 'E' \
						|| data->map[y][x] == 'W')
			{
				color = 0x000000;
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
*/