/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 11:19:29 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/12 14:26:47 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# include <limits.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define W			119
# define S			115
# define A			97
# define D			100

# define Q			113
# define E			101

# define SPACE		32

# define ESC		65307

# define UP			65362
# define DOWN		65364
# define LEFT		65361
# define RIGHT		65363

# define WALL_RES	128

# define SCREENWIDTH	1920
# define SCREENHEIGHT	1080

# define MOVE_SPEED		0.1
# define ROT_SPEED		0.015

# define SQUARE_RES		64

# define FOV		90

# define ERR		2147483648

# define MINI_MAP_SCALE	8 // Example scale factor to reduce the mini map size
# define X_OFFSET		10 // X offset from the screen corner
# define Y_OFFSET		10 // Y offset from the screen corner

# define DOOR_PATH		"./textures/door-.xpm"

# define ANIM_1 "./textures/fire_1.xpm"
# define ANIM_2 "./textures/fire_2.xpm"
# define ANIM_3 "./textures/fire_3.xpm"
# define ANIM_4 "./textures/fire_4.xpm"

/*		STRUCTURES		*/

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_texture
{
	t_image			no;
	t_image			so;
	t_image			ea;
	t_image			we;
	t_image			door;
	t_image			anim_1;
	t_image			anim_2;
	t_image			anim_3;
	t_image			anim_4;
	unsigned int	floor;
	unsigned int	ceiling;
}		t_textures;

typedef struct s_coords
{
	int		x;
	int		y;
}			t_coords;

typedef struct s_coords_f
{
	float	x;
	float	y;
}			t_coords_f;

typedef struct s_player
{
	t_coords_f	pos;
	float		angle;
	int			facing_door;
	int			door_x;
	int			door_y;
}		t_player;

typedef struct s_rcast
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	t_coords_f		pos;
	t_coords_f		dir;
	t_coords_f		plane;
	t_coords_f		raydir;
	t_coords_f		sidedist;
	t_coords_f		deltadist;
	t_coords		map;
	t_coords		step;
	float			step_tex;
	float			camera_x;
	float			line_height;
	float			tex_pos;
	float			perp_wall_dist;
	float			tex_x;
	char			*wall_type;
	char			frame;
	int				x;
	int				y;
	int				side;
	int				index;
	int				draw_end;
	int				draw_start;
}			t_rcast;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_max_y;
	int			map_max_x;
	char		err;
	t_textures	*textures;
	t_player	*player;
	t_image		img;
	t_rcast		*rcast;
}		t_data;

/*		PARSING FUNCTIONS		*/

t_data	*ft_parse_map(char *map_name);
t_data	*ft_read_infos(int fd);

char	ft_get_info(char *line, t_data *data);
char	ft_check_data(t_data *data);
char	ft_is_map_char(char c);
char	ft_pathfinding(t_data *data);
char	ft_only_spaces(t_data *data, char *line, int fd);

char	*ft_strjoin_free(char *s1, char *s2);
char	*ft_check_tex_name(char *line, char	*file, int j);

char	**ft_check_map(char **base_map, t_data *data);

void	ft_get_image(t_data *data, char *line, t_image *img);
void	ft_get_player_coords(t_data *data);

int		ft_strlen_map(char *str);
int		ft_get_color(char *line, unsigned int color);

/*		UTILS FUNCTIONS		*/

void	ft_free_all(t_data *data);

/*		HOOKS		*/

int		ft_close_button(t_data *data);
int		ft_player_move(int keycode, t_data *data);
int		ft_mouse_hook(int x, int y, t_data *param);
void	ft_raycast_horizontal(t_data *data, int angle);

/*		DRAW			*/

void	img_pix_put(t_image *img, int x, int y, int color);
void	ft_create_image(t_data *data);
void	ft_draw_bg(t_data *data);

/*		FI_INIT			*/

int		ft_game_loop(t_data *data);

/*		RAYCASTING			*/

float	ft_deg_to_rad(float a);
float	ft_fix_ang(float a);
void	ft_cast_vertical_ray(t_data *data, float *disV);
void	ft_cast_horizontal_ray(t_data *data, float *disH);
void	ft_draw_rays_2d(t_data *data);
void	ft_raycast(t_data *data);
void	ft_get_side_dist(t_data *data);
char	ft_wall_found(t_data *data);
void	ft_search_wall(t_data *data);
void	ft_calc_wall_dist(t_data *data);

/*		TEXTURE_RAYCAST		*/

void	ft_draw_pix(t_data *data);

/*		MINI_MAP			*/

void	draw_map_element(t_data *data, int mini_map_x, \
	int mini_map_y, int color);
int		ft_put_color(char map_value);
int		ft_should_draw(int mini_map_x, int mini_map_y);
void	ft_draw_mini_map(t_data *data);
void	ft_draw_mini_player(t_data *data);

/*		DOOR			*/

void	ft_interact_door(t_data *data);

#endif