/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:08:16 by abenamar          #+#    #+#             */
/*   Updated: 2024/03/14 16:56:57 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include "float.h"
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
# define __ERR_14	"Error: no camera ('C' identifier) is declared\n"

ssize_t		ft_pstderr(const char *str);
void		ft_perror(const char *str);

void		ft_tab_free(char **tab);
size_t		ft_tab_size(char **tab);

/* ************************************************************************** */
/*                                                                            */
/*                                    math                                    */
/*                                                                            */
/* ************************************************************************** */

# define __M_PIF	3.14159265358979323846F

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

float		ft_atof(const char *nptr);

t_vec3		ft_vec3(float x, float y, float z);
t_vec3		ft_vec3_sum(t_vec3 u, t_vec3 v);
t_vec3		ft_vec3_diff(t_vec3 u, t_vec3 v);
t_vec3		ft_vec3_prod(t_vec3 u, float t);
float		ft_vec3_len(t_vec3 u);
t_vec3		ft_vec3_unit(t_vec3 u);
float		ft_vec3_dot(t_vec3 u, t_vec3 v);
t_vec3		ft_vec3_cross(t_vec3 u, t_vec3 v);
t_vec3		ft_vec3_rotate(t_vec3 u, t_vec3 theta);

/* ************************************************************************** */
/*                                                                            */
/*                                   scene                                    */
/*                                                                            */
/* ************************************************************************** */

typedef t_vec3	t_color;

typedef struct s_ambiance
{
	float	lighting;
	t_color	color;
}	t_ambiance;

typedef t_vec3	t_point3;

typedef struct s_camera
{
	t_point3	position;
	t_vec3		orientation;
	int			fov;
	t_vec3		theta;
}	t_camera;

typedef struct s_light
{
	t_point3	position;
	float		brightness;
	t_color		color;
}	t_light;

typedef struct s_sphere
{
	t_point3	center;
	float		radius;
	t_color		color;
}	t_sphere;

typedef struct s_plane
{
	t_point3	point;
	t_vec3		normal;
	t_color		color;
	t_vec3		theta;
}	t_plane;

typedef struct s_cylinder
{
	t_point3	center;
	t_vec3		axis;
	float		radius;
	float		height;
	t_color		color;
	t_vec3		theta;
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

t_color		ft_color_read(const char *str);
t_vec3		ft_vec3_read(const char *str);
uint8_t		ft_vec3_is_normalized(t_vec3 u);

uint8_t		ft_ambiance_init(t_scene *scene, char **info);
uint8_t		ft_camera_init(t_scene *scene, char **info);
uint8_t		ft_light_add(t_scene *scene, char **info);
uint8_t		ft_sphere_add(t_scene *scene, char **info);
uint8_t		ft_plane_add(t_scene *scene, char **info);
uint8_t		ft_cylinder_add(t_scene *scene, char **info);
void		ft_scene_free(t_scene *scene);
t_scene		*ft_scene_new(const char *file);

/* ************************************************************************** */
/*                                                                            */
/*                                   render                                   */
/*                                                                            */
/* ************************************************************************** */

# ifndef _WIDTH
#  define _WIDTH	320
# endif

# ifndef _HEIGHT
#  define _HEIGHT	180
# endif

# ifndef _TITLE
#  define _TITLE	"MiniRT"
# endif

# ifndef _SAMPLES_PER_PIXEL
#  define _SAMPLES_PER_PIXEL	0
# endif

typedef struct s_xclient
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*buf;
	char		*data;
	int			bpp;
	int			lsize;
	int			endian;
	uint8_t		update;
	t_scene		*scene;
}	t_xclient;

typedef struct s_viewport
{
	t_vec3		u;
	t_vec3		v;
	t_vec3		pdu;
	t_vec3		pdv;
	t_point3	p00;
}	t_viewport;

typedef struct s_ray
{
	t_point3	origin;
	t_vec3		direction;
}	t_ray;

typedef struct s_hit
{
	float		t;
	t_point3	point;
	t_vec3		normal;
	t_color		color;
}	t_hit;

void		ft_xclient_free(t_xclient *xclient);
t_xclient	*ft_xclient_new(t_scene *scene);
void		ft_xclient_buffer(t_xclient *xclient);
void		ft_xclient_flush(t_xclient *xclient);

t_viewport	ft_viewport(t_camera *camera);
t_ray		ft_ray(t_point3 origin, t_vec3 direction);
void		ft_cylinder_hit(t_cylinder *cy, t_ray r, t_hit *h);
t_color		ft_scene_hit(t_scene *scene, t_ray r);

int			ft_pixel_color(t_color color, int spp);
void		ft_pixel_put(t_xclient *xclient, int x, int y, int color);
void		ft_ray_tracing(t_xclient *xclient);
int			ft_key_press(int keycode, t_xclient *xclient);

#endif
