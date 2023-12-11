/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:15:29 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/11 11:24:12 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	ft_is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'D' || c == 'N' || c == 'D' || c == '2'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

char	ft_get_info(char *line, t_data *data)
{
	int		i;

	i = 0;
	if (!*line)
		return (1);
	if (!data->textures->no.mlx_img && !ft_strncmp(line, "NO ", 3))
		data->textures->no.mlx_img = ft_get_image(line, data);
	else if (!data->textures->so.mlx_img && !ft_strncmp(line, "SO ", 3))
		data->textures->so.mlx_img = ft_get_image(line, data);
	else if (!data->textures->ea.mlx_img && !ft_strncmp(line, "EA ", 3))
		data->textures->ea.mlx_img = ft_get_image(line, data);
	else if (!data->textures->we.mlx_img && !ft_strncmp(line, "WE ", 3))
		data->textures->we.mlx_img = ft_get_image(line, data);
	else if (!ft_strncmp(line, "F ", 2))
		data->textures->floor = ft_get_color(line);
	else if (!ft_strncmp(line, "C ", 2))
		data->textures->ceiling = ft_get_color(line);
	else
	{
		while (!ft_isprint(line[i]))
			i++;
		if (line[i])
			return (0);
		return (0);
	}
	return (1);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		str[j++] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		str[j++] = s2[i];
		i++;
	}
	str[j] = 0;
	free(s1);
	free(s2);
	return (str);
}

void	ft_init_textures(t_data *data)
{
	data->textures->no.addr = mlx_get_data_addr(data->textures->no.mlx_img, \
		&data->textures->no.bpp, &data->textures->no.line_len, \
			&data->textures->no.endian);
	data->textures->so.addr = mlx_get_data_addr(data->textures->so.mlx_img, \
		&data->textures->so.bpp, &data->textures->so.line_len, \
			&data->textures->so.endian);
	data->textures->ea.addr = mlx_get_data_addr(data->textures->ea.mlx_img, \
		&data->textures->ea.bpp, &data->textures->ea.line_len, \
			&data->textures->ea.endian);
	data->textures->we.addr = mlx_get_data_addr(data->textures->we.mlx_img, \
		&data->textures->we.bpp, &data->textures->we.line_len, \
			&data->textures->we.endian);
	int	res = WALL_RES;
	data->textures->door.mlx_img = mlx_xpm_file_to_image(data->mlx, DOOR_PATH, &res, &res);
	data->textures->door.addr = mlx_get_data_addr(data->textures->door.mlx_img, \
		&data->textures->door.bpp, &data->textures->door.line_len, \
			&data->textures->door.endian);
	data->textures->anim_1.mlx_img = mlx_xpm_file_to_image(data->mlx, ANIM_1, &res, &res);
	data->textures->anim_1.addr = mlx_get_data_addr(data->textures->anim_1.mlx_img, \
		&data->textures->anim_1.bpp, &data->textures->anim_1.line_len, \
			&data->textures->anim_1.endian);
		data->textures->anim_2.mlx_img = mlx_xpm_file_to_image(data->mlx, ANIM_2, &res, &res);
	data->textures->anim_2.addr = mlx_get_data_addr(data->textures->anim_2.mlx_img, \
		&data->textures->anim_2.bpp, &data->textures->anim_2.line_len, \
			&data->textures->anim_2.endian);
		data->textures->anim_3.mlx_img = mlx_xpm_file_to_image(data->mlx, ANIM_3, &res, &res);
	data->textures->anim_3.addr = mlx_get_data_addr(data->textures->anim_3.mlx_img, \
		&data->textures->anim_3.bpp, &data->textures->anim_3.line_len, \
			&data->textures->anim_3.endian);
		data->textures->anim_4.mlx_img = mlx_xpm_file_to_image(data->mlx, ANIM_4, &res, &res);
	data->textures->anim_4.addr = mlx_get_data_addr(data->textures->anim_4.mlx_img, \
		&data->textures->anim_4.bpp, &data->textures->anim_4.line_len, \
			&data->textures->anim_4.endian);
}

char	ft_check_data(t_data *data)
{
	if (!data->textures->no.mlx_img || !data->textures->so.mlx_img
		|| !data->textures->ea.mlx_img || !data->textures->we.mlx_img)
		return (0);
	ft_init_textures(data);
	if (data->textures->floor == ERR
		|| data->textures->ceiling == ERR)
		return (0);
	if (!data->map)
		return (0);
	if (!ft_pathfinding(data))
		return (0);
	return (1);
}
