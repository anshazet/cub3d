/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:15:04 by ashalagi          #+#    #+#             */
/*   Updated: 2023/11/28 15:32:10 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

# define W			119
# define S			115
# define A			97
# define D			100

# define ESC		65307

# define UP			65362
# define DOWN		65364
# define LEFT		65361
# define RIGHT		65363

# define WALL_RES   500

# define SCREENWIDTH 640
# define SCREENHEIGHT 480

/*      STRUCTURES      */

typedef struct s_textures
{
	void			*no;
	void			*so;
	void			*ea;
	void			*we;
	unsigned int	floor;
	unsigned int	ceiling;
}		t_textures;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	t_textures	*textures;
}		t_data;

/*      PARSING FUNCTIONS       */

t_data	*ft_parse_map(char *map_name);
t_data	*ft_read_infos(int fd);

char	ft_get_info(char *line, t_data *data);
char	ft_check_data(t_data *data);

void	*ft_get_image(char *line, t_data *data);

int		ft_get_color(char *line);

/*      UTILS FUNCTIONS         */

void	ft_free_all(t_data *data);

/*			HOOKS			*/

int	ft_close_button(t_data *data);

#endif