/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:08:16 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 18:04:40 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <math.h>
# include <X11/Xlib.h>
# include <X11/Xutil.h>
# include "mlx.h"
# include "libft.h"

/* ************************************************************************** */
/*                                                                            */
/*                                   utils                                    */
/*                                                                            */
/* ************************************************************************** */

# define __USAGE	"Usage: miniRT file.rt\n"
# define __ERR_1	"Error: wrong file extension (not *.rt)\n"
# define __ERR_2	"Error: out of memory\n"
# define __ERR_3	"Error: capital letter element declared more than once\n"
# define __ERR_4	"Error: wrong number of element informations\n"
# define __ERR_5	"Error: element information is NaN (not a number)\n"
# define __ERR_6	"Error: invalid lightning ratio (not in range [0,1])\n"
# define __ERR_7	"Error: wrong number of RGB colors (not 3)\n"
# define __ERR_8	"Error: invalid value in RGB color (not in range [0,255])\n"
# define __ERR_9	"Error: wrong number of 3D vector coordinates (not 3)\n"
# define __ERR_10	"Error: invalid normalized value (not in range [-1,1])\n"
# define __ERR_11	"Error: invalid field of view (not in range [0,180])\n"
# define __ERR_12	"Error: wrong element identifier (not A,C,L,sp,pl,cy)\n"
# define __ERR_13	"Error: invalid distance (not greater or equal to 0)\n"

ssize_t		ft_pstderr(const char *str);
void		ft_perror(const char *str);

void		ft_tab_free(char **tab);
size_t		ft_tab_size(char **tab);

/* ************************************************************************** */
/*                                                                            */
/*                                    math                                    */
/*                                                                            */
/* ************************************************************************** */

# ifndef M_PI
#  define M_PI	3.14159265358979323846	/* pi */
# endif

typedef struct s_vec2
{
	int	x;
	int	y;
}	t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

double		ft_atof(const char *nptr);

t_vec3		*ft_vec3_init(const char *str);

/* ************************************************************************** */
/*                                                                            */
/*                                   scene                                    */
/*                                                                            */
/* ************************************************************************** */

typedef struct s_ambiance
{
	double	lratio;
	int		color;
}	t_ambiance;

typedef struct s_camera
{
	t_vec3	position;
	t_vec3	orientation;
	int		fov;
}	t_camera;

typedef struct s_light
{
	t_vec3	position;
	double	bratio;
	int		color;
}	t_light;

typedef struct s_sphere
{
	t_vec3	center;
	double	diameter;
	int		color;
}	t_sphere;

typedef struct s_plane
{
	t_vec3	point;
	t_vec3	orientation;
	int		color;
}	t_plane;

typedef struct s_cylinder
{
	t_vec3	center;
	t_vec3	orientation;
	double	diameter;
	double	height;
	int		color;
}	t_cylinder;

typedef struct s_scene
{
	t_ambiance	*ambiance;
	t_camera	*camera;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*cylinders;
}	t_scene;

int			ft_color_init(const char *str);

uint8_t		ft_ambiance_init(t_scene *scene, char **info);
uint8_t		ft_camera_init(t_scene *scene, char **info);
uint8_t		ft_light_add(t_scene *scene, char **info);
uint8_t		ft_shape_add(t_scene *scene, char **info);

void		ft_scene_free(t_scene *scene);
t_scene		*ft_scene_new(char *file);

/* ************************************************************************** */
/*                                                                            */
/*                                   render                                   */
/*                                                                            */
/* ************************************************************************** */

# ifndef WIDTH
#  define WIDTH		1280
# endif

# ifndef HEIGHT
#  define HEIGHT	720
# endif

# ifndef TITLE
#  define TITLE		"MiniRT"
# endif

typedef struct s_xsettings
{
	t_scene	*scene;
	t_vec2	origin;
	t_vec3	theta;
}	t_xsettings;

typedef struct s_ximage
{
	void		*mlx;
	void		*img;
	char		*data;
	int			bpp;
	int			lsize;
	int			endian;
	t_xsettings	xsettings;
}	t_ximage;

typedef struct s_xclient
{
	t_xsettings	xsettings;
	void		*mlx;
	void		*win;
	t_ximage	ximage;
}	t_xclient;

void		ft_xsettings_reset(t_xsettings *xsettings);
t_ximage	ft_ximage_init(t_xclient *xclient);
void		ft_xclient_free(t_xclient *xclient);
t_xclient	*ft_xclient_new(t_scene *scene);

void		ft_pixel_put(t_ximage ximage, int x, int y, int color);
int			ft_frame_render(t_xclient *xclient);

int			ft_key_press_handle(int keycode, t_xclient *xclient);

#endif
