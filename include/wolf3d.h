#ifndef RTV1_H
# define RTV1_H
# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <pthread.h>
# include "x11.h"

# define WIDTH 		900
# define HEIGHT		600

# define NUM_THREADS	9

# define SPEED		0.1
# define MOVE_FORWARD	0b00000001
# define MOVE_BACKWARD 	0b00000010
# define STRAFE_LEFT 	0b00000100
# define STRAFE_RIGHT 	0b00001000
# define ROTATE_RIGHT 	0b00010000
# define ROTATE_LEFT 	0b00100000

# define NORTH			0
# define EAST			1
# define SOUTH			2
# define WEST			3

# define TEXTURE_WIDTH	64
# define TEXTURE_HEIGHT	64

typedef struct		s_texture
{
	char			*dir;
	int				len;
	int				*number;
	void			**tex;
}					t_texture;

typedef struct		s_cam
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			plane;
}					t_cam;

typedef struct		s_ray
{
	t_vec2d			pos;
	t_vec2d			dir;
	t_vec2d			d_side;
	t_vec2d			d_delta;
	t_vec2d			step;
	t_bool			hit;
	t_bool			side;
	int				orientation;
	int				mapx;
	int				mapy;
	double			wall;
}					t_ray;

typedef struct		s_line
{
	t_vec2d			start;
	t_vec2d			end;
	t_frgba			col;
	t_bool			side;
	int				orientation;
	int				tex_nu;
	int				height;
}					t_line;

typedef struct		s_map
{
	int				h;
	int				w;
	int				*block;
	int				max;
	char			*name;
	t_texture		tex;
	t_bool			texture;
}					t_map;

typedef struct		s_mlx
{
	char			*adr;
	int				bpp;
	int				end;
	int				sln;
	void			*img;
	void			*mlx;
	void			*win;
}					t_mlx;

typedef struct		s_env
{
	t_mlx			mlx;
	t_cam			cam;
	t_map			map;
	t_ray			ray[NUM_THREADS];
	t_line			line[NUM_THREADS];
	int8_t			event;
}					t_env;

typedef struct		s_thread_data
{
	t_env			*e;
	int				id;
	int				start;
	int				stop;
}					t_thread_data;

typedef struct		s_thread
{
	pthread_t		thread[NUM_THREADS];
	t_thread_data	thread_data[NUM_THREADS];
	pthread_attr_t	attr;
	void			*status;
}					t_thread;

/*
** ===================== MAIN.C ==============================
*/
void				render(t_env *e);
/*
** ===================== INIT.C =-============================
** init_null_secure
** init_map
** init_cam
*/
void				init_env(t_env *e, const char *file);
/*
** ===================== GET_MAP_INFO.C ======================
** stock_map_info
** stock_map_name
*/
int					get_map_info(t_env *e, const int fd);
/*
** ===================== GET_MAP_TEXTURE.C ===================
*/
int					get_map_texture(t_env *e, const int fd);
/*
** ===================== GET_MAP_BLOCK.C =====================
** check_map_block
** stock_map_block
** check_map_block
*/
int					get_map_block(t_env *e, const int fd);
/*
**
*/
void				floor_cast(t_env *e, int x, int id);
/*
** ===================== RAY.C ===============================
** ray_init_calc
** ray_step_calc
** ray_cast_dda
** ray_wall_calc
*/
void				ray_cast(t_env *e, int x, int id);
/*
** ===================== LINE.C ==============================
** line_init_calc
** line_set_basic_color
** line_set_text_num
** line_get_type
*/
void				line_cast(t_env *e, int x, int id);
/*
** ===================== LINE_DRAW.C =========================
** shadow
*/
void				line_basic_draw(t_env *e, t_line *line, int x);
void				line_textu_draw(t_env *e, t_line *line, t_ray *ray, int x);
/*
** ===================== GRAPHIC.C ===========================
*/
void				img_pixel_put(t_env *e, int x, int y, t_frgba c);
void				img_fill(t_env *e, t_frgba c);
void				hello_world(t_env *e);
/*
** ===================== INPUT.C =============================
*/
int					red_cross(int key, t_env *e);
int					key_pressed(int key, t_env *e);
int					key_released(int key, t_env *e);
int					key_loop(t_env *e);
/*
** ===================== MOVEMENT.C ==========================
*/
void				move(t_env *e, int key);
void				strafe(t_env *e, int key);
void				rotate(t_env *e, int key);
/*
** ===================== UTILS.C =============================
*/
void				checkout(t_env *e, char *s);
void				show_block(int *arr, int w, size_t len);
void				hello_world(t_env *e);
/*
** ===================== PTHREAD.C ==========================
** thread_init_data
** thread_render_part
** thread_create
** thread_join
*/
void				thread_process(t_env *e, t_thread *t);
/*
** ===================== INIT.C =-=========================
** init_null_secure
** init_map
** init_cam
*/
void				init_env(t_env *e, const char *file);
/*
** ===================== GET_MAP_INFO.C ===================
** stock_map_info
** stock_map_name
*/
int					get_map_info(t_env *e, const int fd);
/*
** ===================== GET_MAP_BLOCK.C ==================
** check_map_block
** stock_map_block
** check_map_block
*/
int					get_map_block(t_env *e, const int fd);

#endif
