/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:45:26 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/11 13:35:44 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

void	ft_init_raycast(t_data *data)
{
	data->rcast->pos.x = data->player->pos.x;
	data->rcast->pos.y = data->player->pos.y;
	data->rcast->dir.y = cosf(ft_deg_to_rad(data->player->angle));
	data->rcast->dir.x = sinf(ft_deg_to_rad(data->player->angle));
	data->rcast->plane.x = cosf(ft_deg_to_rad(FOV) / 2.0) * -data->rcast->dir.y;
	data->rcast->plane.y = sinf(ft_deg_to_rad(FOV) / 2.0) * data->rcast->dir.x;
	data->rcast->x = 0;
}

void	ft_calc_vectors(t_data *data)
{
	data->rcast->camera_x = 2.0 * data->rcast->x / SCREENWIDTH - 1.0;
	data->rcast->raydir.x = data->rcast->dir.x \
		+ data->rcast->plane.x * data->rcast->camera_x;
	data->rcast->raydir.y = data->rcast->dir.y \
		+ data->rcast->plane.y * data->rcast->camera_x;
	data->rcast->map.x = data->rcast->pos.x;
	data->rcast->map.y = data->rcast->pos.y;
	if (data->rcast->raydir.x == 0)
		data->rcast->deltadist.x = 1e30;
	else
		data->rcast->deltadist.x = fabs((1.0 / data->rcast->raydir.x));
	if (data->rcast->raydir.y == 0)
		data->rcast->deltadist.y = 1e30;
	else
		data->rcast->deltadist.y = fabs((1.0 / data->rcast->raydir.y));
}

void	ft_get_side_dist(t_data *data)
{
	if (data->rcast->raydir.x < 0)
	{
		data->rcast->step.x = -1;
		data->rcast->sidedist.x = (data->rcast->pos.x - data->rcast->map.x) \
			* data->rcast->deltadist.x;
	}
	else
	{
		data->rcast->step.x = 1;
		data->rcast->sidedist.x = (data->rcast->map.x + 1.0 \
			- data->rcast->pos.x) * data->rcast->deltadist.x;
	}
	if (data->rcast->raydir.y < 0)
	{
		data->rcast->step.y = -1;
		data->rcast->sidedist.y = (data->rcast->pos.y \
			- data->rcast->map.y) * data->rcast->deltadist.y;
	}
	else
	{
		data->rcast->step.y = 1;
		data->rcast->sidedist.y = (data->rcast->map.y + 1.0 \
			- data->rcast->pos.y) * data->rcast->deltadist.y;
	}
}

char	ft_wall_found(t_data *data)
{
	if (data->rcast->map.x >= 0 && data->rcast->map.x <= data->map_max_x \
		&& data->rcast->map.y >= 0 && data->rcast->map.y < data->map_max_y)
	{
		if ((data->map[data->rcast->map.y][data->rcast->map.x] >= '1' && \
			data->map[data->rcast->map.y][data->rcast->map.x] <= '5') || \
			data->map[data->rcast->map.y][data->rcast->map.x] == 'D')
		{
			data->rcast->wall_type = \
				&data->map[data->rcast->map.y][data->rcast->map.x];
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

void	ft_search_wall(t_data *data)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->rcast->sidedist.x < data->rcast->sidedist.y)
		{
			data->rcast->sidedist.x += data->rcast->deltadist.x;
			data->rcast->map.x += data->rcast->step.x;
			data->rcast->side = 0;
		}
		else
		{
			data->rcast->sidedist.y += data->rcast->deltadist.y;
			data->rcast->map.y += data->rcast->step.y;
			data->rcast->side = 1;
		}
		hit = ft_wall_found(data);
	}
}

void	ft_calc_wall_dist(t_data *data)
{
	if (data->rcast->side == 0)
		data->rcast->perp_wall_dist = (data->rcast->sidedist.x \
			- data->rcast->deltadist.x);
	else
		data->rcast->perp_wall_dist = (data->rcast->sidedist.y \
			- data->rcast->deltadist.y);
	data->rcast->line_height = (int)(SCREENHEIGHT / data->rcast->perp_wall_dist);
	data->rcast->draw_start = -data->rcast->line_height / 2 + SCREENHEIGHT / 2;
	if (data->rcast->draw_start < 0)
		data->rcast->draw_start = 0;
	data->rcast->draw_end = data->rcast->line_height / 2 + SCREENHEIGHT / 2;
	if (data->rcast->draw_end >= SCREENHEIGHT)
		data->rcast->draw_end = SCREENHEIGHT - 1;

	float wall_x;
	if (data->rcast->side == 0)
		wall_x = data->player->pos.y + data->rcast->perp_wall_dist * data->rcast->raydir.y;
	else
		wall_x = data->player->pos.x + data->rcast->perp_wall_dist * data->rcast->raydir.x;
	wall_x -= floor((wall_x));
	data->rcast->tex_x = (int)(wall_x * WALL_RES);
	if (data->rcast->side == 0 && data->rcast->raydir.x > 0)
		data->rcast->tex_x = WALL_RES - data->rcast->tex_x - 1;
	if (data->rcast->side == 1 && data->rcast->raydir.y < 0)
		data->rcast->tex_x = WALL_RES - data->rcast->tex_x - 1;
}

void	ft_get_pix_wall_S_N(t_data *data)
{
	if (data->rcast->raydir.y > 0.0)
	{
		data->rcast->red = data->textures->so.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->so.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->so.addr[data->rcast->index];
	}
	else
	{
		data->rcast->red = data->textures->no.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->no.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->no.addr[data->rcast->index];
	}
}

void	ft_get_pix_wall_E_W(t_data *data)
{
	if (data->rcast->raydir.x > 0.0)
	{
		data->rcast->red = data->textures->ea.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->ea.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->ea.addr[data->rcast->index];
	}
	else
	{
		data->rcast->red = data->textures->we.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->we.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->we.addr[data->rcast->index];
	}
}

void	ft_get_pix_layer(t_data *data, t_image *anim)
{
	data->rcast->red = anim->addr[data->rcast->index + 2];
	data->rcast->green = anim->addr[data->rcast->index + 1];
	data->rcast->blue = anim->addr[data->rcast->index];
	if (!data->rcast->red && !data->rcast->blue && data->rcast->green == 255)
	{
		if (data->rcast->side)
			ft_get_pix_wall_S_N(data);
		else
			ft_get_pix_wall_E_W(data);
	}
}

void	ft_get_pix_frame(t_data *data)
{
	if (data->rcast->frame == 1)
		ft_get_pix_layer(data, &data->textures->anim_1);
	else if (data->rcast->frame == 2)
		ft_get_pix_layer(data, &data->textures->anim_2);
	else if (data->rcast->frame == 3)
		ft_get_pix_layer(data, &data->textures->anim_3);
	else
		ft_get_pix_layer(data, &data->textures->anim_4);
}

void	ft_draw_pix(t_data *data)
{
	int	tex_y = (int) data->rcast->tex_pos & (WALL_RES - 1);
	data->rcast->tex_pos += data->rcast->step_tex;
	data->rcast->index = floorf((tex_y * data->textures->no.line_len) \
		+ (data->rcast->tex_x * (data->textures->no.bpp / 8)));
	if (*data->rcast->wall_type == 'D')
		ft_get_pix_layer(data, &data->textures->door);
	else if (*data->rcast->wall_type == '2')
		ft_get_pix_frame(data);
	else
	{
		if (data->rcast->side)
			ft_get_pix_wall_S_N(data);
		else
			ft_get_pix_wall_E_W(data);
	}
	img_pix_put(&data->img, data->rcast->x, data->rcast->y, \
		((data->rcast->red << 16) + (data->rcast->green << 8) \
		+ data->rcast->blue));
	data->rcast->y++;
}

void	ft_raycast(t_data *data)
{
	ft_init_raycast(data);
	while (data->rcast->x < SCREENWIDTH)
	{
		ft_calc_vectors(data);
		ft_get_side_dist(data);
		ft_search_wall(data);
		ft_calc_wall_dist(data);
		data->rcast->step_tex = 1.0 * (float) WALL_RES / data->rcast->line_height;
		data->rcast->tex_pos = (data->rcast->draw_start - SCREENHEIGHT / 2 + data->rcast->line_height / 2) * data->rcast->step_tex;
		data->rcast->y = data->rcast->draw_start;
		while (data->rcast->y < data->rcast->draw_end)
			ft_draw_pix(data);
		data->rcast->x++;
	}
	if (data->rcast->frame >= 1 && data->rcast->frame <= 3)
		data->rcast->frame++;
	else
		data->rcast->frame = 1;
}
