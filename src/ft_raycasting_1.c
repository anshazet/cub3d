/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:13:51 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/04 11:01:37 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float ft_deg_to_rad(float a)
{
    return (a * M_PI / 180.0);
}

float ft_fix_ang(float a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return a;
}

void ft_cast_vertical_ray(t_data *data, float *disV)
{
	float	Tan;
	int		dof;

	dof = 0;
	*disV = 100000;
	Tan = tan(ft_deg_to_rad(data->rcast.ra));

	if (cos(ft_deg_to_rad(rcast->ra)) > 0.001)
	{
		rcast->rx = (((int)rcast->px >> 6) << 6) + SQUARE_RES;
		rcast->ry = (rcast->px - rcast->rx) * Tan + rcast->py;
		rcast->xo = 64;
		rcast->yo = -rcast->xo * Tan;
	}
	else if (cos(ft_deg_to_rad(rcast->ra)) < -0.001)
	{
		rcast->rx = (((int)rcast->px >> 6) << 6) - 0.0001;
		rcast->ry = (rcast->px - rcast->rx) * Tan + rcast->py;
		rcast->xo = -64;
		rcast->yo = - rcast->xo * Tan;
	}
	else
	{
		rcast->rx = rcast->px;
		rcast->ry = rcast->py;
		dof = 8; // looking up or down, no hit
	}
	while (dof < 8)
	{
		rcast->mx = (int)(rcast->rx) >> 6;
		rcast->my = (int)(rcast->ry) >> 6;
		rcast->mp = rcast->my * rcast->mapX + rcast->mx;
		if (rcast->mp > 0 && rcast->mp < rcast->mapX * rcast->mapY && rcast->map[rcast->mp] == 1)
		{
			dof = 8;
			*disV = cos(ft_deg_to_rad(rcast->ra)) * (rcast->rx - rcast->px) - sin(ft_deg_to_rad(rcast->ra)) * (rcast->ry - rcast->py); // hit
		}
		else
		{
			rcast->rx += rcast->xo;
			rcast->ry += rcast->yo;
			dof += 1; // check next horizontal
		}
	}
}

void ft_cast_horizontal_ray(t_rcast *rcast, float *disH)
{
	float	Tan;
	int		dof;

	dof = 0;
	*disH = 100000;
	Tan = 1.0 / tan(ft_deg_to_rad(rcast->ra));

	if (sin(ft_deg_to_rad(rcast->ra)) > 0.001)
	{
		rcast->ry = (((int)rcast->py >> 6) << 6) - 0.0001;
		rcast->rx = (rcast->py - rcast->ry) * Tan + rcast->px;
		rcast->yo = -64;
		rcast->xo = - rcast->yo * Tan;
	}
	else if (sin(ft_deg_to_rad(rcast->ra)) < -0.001)
	{
		rcast->ry = (((int)rcast->py >> 6) << 6) + SQUARE_RES;
		rcast->rx = (rcast->py - rcast->ry) * Tan + rcast->px;
		rcast->yo = 64;
		rcast->xo = - rcast->yo * Tan;
	}
	else
	{
		rcast->rx = rcast->px;
		rcast->ry = rcast->py;
		dof = 8; // looking straight left or right, no hit
	}

	while (dof < 8)
	{
		rcast->mx = (int)(rcast->rx) >> 6;
		rcast->my = (int)(rcast->ry) >> 6;
		rcast->mp = rcast->my * rcast->mapX + rcast->mx;
		if (rcast->mp > 0 && rcast->mp < rcast->mapX * rcast->mapY && rcast->map[rcast->mp] == 1)
		{
			dof = 8;
			*disH = cos(ft_deg_to_rad(rcast->ra)) * (rcast->rx - rcast->px) - sin(ft_deg_to_rad(rcast->ra)) * (rcast->ry - rcast->py); // hit
		}
		else
		{
			rcast->rx += rcast->xo;
			rcast->ry += rcast->yo;
			dof += 1; // check next horizontal
		}
	}
}

void ft_draw_rays_2d(t_data *data)
{
//	int r;
	float disV, disH;
//	float vx;
//	float vy;
	float used_distance, ca, r;

	float angle_max = 90;

	data->rcast.ra = ft_fix_ang(data->rcast.pa + 30); // ray set back 30 degrees
	r = 0;
	while (r < angle_max)
	{
		ft_cast_vertical_ray(&data->rcast, &disV);
//		vx = rcast->rx;
//		vy = rcast->ry;
		ft_cast_horizontal_ray(&data->rcast, &disH);

		int color = 0x00FF00; // Some color for the ray

		if (disV < disH) //vertical distance is smaller
		{
//			rcast->rx = vx;
//			rcast->ry = vy;
			used_distance = disV;
			disH = disV;
			color = 0x006600; // Different color for vertical hit
		}
		else // Horizontal distance is smaller or equal
		{
			used_distance = disH;
			color = 0x00FF00; // Different color for horizontal hit
		}

		ca = ft_fix_ang(data->rcast.pa - data->rcast.ra);
		used_distance = used_distance * cos(ft_deg_to_rad(ca)); // Correct distance

		ft_draw_wall(data, r * SCREENWIDTH  / angle_max , used_distance, color);

		data->rcast.ra = ft_fix_ang(data->rcast.ra - 1); // Go to next ray
		r++;
	}
}