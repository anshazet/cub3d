/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:13:51 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/05 15:21:12 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float ft_deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

void	vector_distance(t_data *data)
{
	t_coords_f	pos;
	t_coords_f	dir;
	t_coords_f	plane;

	pos.x = data->player->pos->x;
	pos.y = data->player->pos->y;
	dir.y = cosf(ft_deg_to_rad(data->player->angle));
	dir.x = sinf(ft_deg_to_rad(data->player->angle));
	plane.x = cosf(FOV / 2.0) * -dir.y;
	plane.y = sinf(FOV / 2.0) * dir.x;

	int x = 0;
	while (x < SCREENWIDTH)
	{
		float	camerax = 2.0 * x / SCREENWIDTH - 1.0;
		t_coords_f	raydir;
		raydir.x = dir.x + plane.x * camerax;
		raydir.y = dir.y + plane.y * camerax;

		t_coords	map;
		map.x = pos.x;
		map.y = pos.y;

		t_coords_f	sidedist;
		t_coords_f	deltadist;
		if (raydir.x == 0)
			deltadist.x = 1e30;
		else
			deltadist.x = fabs((1.0 / raydir.x));
		if (raydir.y == 0)
			deltadist.y = 1e30;
		else
			deltadist.y = fabs((1.0 / raydir.y));
		float	perpWallDist;

		t_coords	step;
		int		hit = 0;
		int		side;

		if (raydir.x < 0)
		{
			step.x = -1;
			sidedist.x = (pos.x - map.x) * deltadist.x;
		}
		else
		{
			step.x = 1;
			sidedist.x = (map.x + 1.0 - pos.x) * deltadist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			sidedist.y = (pos.y - map.y) * deltadist.y;
		}
		else
		{
			step.y = 1;
			sidedist.y = (map.y + 1.0 - pos.y) * deltadist.y;
		}

		while (hit == 0)
		{
			if (sidedist.x < sidedist.y)
			{
				sidedist.x += deltadist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				sidedist.y += deltadist.y;
				map.y += step.y;
				side = 1;
			}
			if (map.x >= 0 && map.x <= data->map_max_x && map.y >= 0 && map.y < data->map_max_y)
			{
				if (data->map[map.y][map.x] == '1')
					hit = 1;
			}
			else
			{
				break ;
			}
		}
		if (side == 0)
			perpWallDist = (sidedist.x - deltadist.x);
		else
			perpWallDist = (sidedist.y - deltadist.y);
		int lineHeight = (int)(SCREENHEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawEnd >= SCREENHEIGHT)
			drawEnd = SCREENHEIGHT - 1;
		while (drawStart < drawEnd)
			img_pix_put(&data->img, x, drawStart++, 0xFFFFFF);
		x++;
	}
}
