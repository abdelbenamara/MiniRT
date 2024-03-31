/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/28 18:08:16 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/01 01:13:05 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include "float.h"
# include <math.h>
# include <stdbool.h>
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

ssize_t		ft_pstderr(char const *str);
void		ft_perror(char const *str);

void		ft_tab_free(char **tab);
size_t		ft_tab_size(char *const *tab);

/* ************************************************************************** */
/*                                                                            */
/*                                    math                                    */
/*                                                                            */
/* ************************************************************************** */

# define __M_PIF	3.14159265358979323846F

typedef struct s_vec3f
{
	float	x;
	float	y;
	float	z;
}	t_vec3f;

typedef struct s_quat4f
{
	t_vec3f	xyz;	
	float	w;
}	t_quat4f;

float		ft_atof(char const *nptr);

t_vec3f		ft_vec3f(float const x, float const y, float const z);
t_vec3f		ft_vec3f_sum(t_vec3f const u, t_vec3f const v);
t_vec3f		ft_vec3f_diff(t_vec3f const u, t_vec3f const v);
t_vec3f		ft_vec3f_prod(t_vec3f const u, float const t);
t_vec3f		ft_vec3f_unit(t_vec3f const u);
float		ft_vec3f_dot(t_vec3f const u, t_vec3f const v);
t_vec3f		ft_vec3f_cross(t_vec3f const u, t_vec3f const v);

t_quat4f	ft_quat4f(t_vec3f const xyz, float const w);
t_quat4f	ft_quat4f_prod(t_quat4f const q, t_quat4f const p);
t_quat4f	ft_quat4f_unit(t_quat4f const q);

/* ************************************************************************** */
/*                                                                            */
/*                                   scene                                    */
/*                                                                            */
/* ************************************************************************** */

typedef t_vec3f	t_color3f;

typedef struct s_ambiance
{
	float		lighting;
	t_color3f	color;
}	t_ambiance;

typedef t_vec3f	t_point3f;

typedef struct s_camera
{
	t_point3f	position;
	t_vec3f		orientation;
	float		fov;
	t_quat4f	rotation;
	t_vec3f		vup;
}	t_camera;

typedef struct s_light
{
	t_point3f	position;
	float		brightness;
	t_color3f	color;
}	t_light;

typedef struct s_sphere
{
	t_point3f	center;
	float		radius;
	float		radius_squared;
	float		radius_reciprocal;
	t_color3f	color;
}	t_sphere;

typedef struct s_plane
{
	t_point3f	point;
	t_vec3f		normal;
	t_color3f	color;
}	t_plane;

typedef struct s_cylinder
{
	t_point3f	top;
	t_point3f	base;
	t_vec3f		axis;
	float		radius;
	float		radius_squared;
	float		radius_reciprocal;
	float		height;
	t_color3f	color;
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

t_color3f	ft_color3f_read(char const *str);
t_vec3f		ft_vec3f_read(char const *str);
bool		ft_vec3f_isnormalized(t_vec3f const u);

bool		ft_ambiance_init(t_scene *const scene, char *const *info);
bool		ft_camera_init(t_scene *const scene, char *const *info);
bool		ft_light_add(t_scene *const scene, char *const *info);
bool		ft_sphere_add(t_scene *const scene, char *const *info);
bool		ft_plane_add(t_scene *const scene, char *const *info);
bool		ft_cylinder_add(t_scene *const scene, char *const *info);
void		ft_scene_free(t_scene *scene);
t_scene		*ft_scene_new(char const *file);

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
#  define _SAMPLES_PER_PIXEL	1
# endif

typedef struct s_xclient
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			lsize;
	int			endian;
	bool		update;
	t_scene		*scene;
}	t_xclient;

typedef struct s_viewport
{
	t_vec3f		u;
	t_vec3f		v;
	t_vec3f		pdu;
	t_vec3f		pdv;
	t_point3f	p00;
}	t_viewport;

typedef struct s_ray
{
	t_point3f	origin;
	t_vec3f		direction;
}	t_ray;

typedef struct s_hit
{
	float		t;
	t_point3f	point;
	t_vec3f		normal;
	t_color3f	color;
}	t_hit;

typedef struct s_basis
{
	t_vec3f	x;
	t_vec3f	y;
	t_vec3f	z;
}	t_basis;

void		ft_xclient_free(t_xclient *xclient);
t_xclient	*ft_xclient_new(t_scene *const scene);

t_ray		ft_ray(t_point3f const origin, t_vec3f const direction);
t_vec3f		ft_face_normal(t_vec3f const direction, t_vec3f const normal);
void		ft_sphere_hit(t_sphere *const sp, t_ray const r, t_hit *const h);
void		ft_plane_hit(t_plane *const pl, t_ray const r, t_hit *const h);
void		ft_cylinder_hit(t_cylinder *const cy, \
				t_ray const r, t_hit *const h);

void		ft_pixel_put(t_xclient const *const xclient, \
				int const x, int const y, t_color3f const color);
void		ft_ray_tracing(t_xclient const *const xclient);
t_basis		ft_basis(t_vec3f const x, t_vec3f const y, t_vec3f const z);
t_vec3f		ft_vec3f_rotate(t_vec3f const u, t_quat4f const q);
int			ft_key_press(int const keycode, t_xclient *const xclient);

#endif
