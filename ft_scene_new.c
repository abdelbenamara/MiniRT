/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:00:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/02/20 23:28:44 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static uint8_t	ft_ambiance_init(t_scene *scene, char **info)
{
	if (scene->ambiance)
		return (ft_pstderr(__ERR_3), 0);
	if (ft_tab_size(info) != 3)
		return (ft_pstderr(__ERR_4), 0);
	scene->ambiance = malloc(sizeof(t_ambiance));
	if (!scene->ambiance)
		return (ft_pstderr(__ERR_2), 0);
	scene->ambiance->lratio = ft_atof(info[1]);
	if (isnan(scene->ambiance->lratio))
		return (ft_pstderr(__ERR_5), 0);
	if (scene->ambiance->lratio < 0.0 || scene->ambiance->lratio > 1.0)
		return (ft_pstderr(__ERR_6), 0);
	scene->ambiance->color = ft_color_read(info[2]);
	if (isnan(scene->ambiance->color.x))
		return (0);
	return (1);
}

static uint8_t	ft_camera_init(t_scene *scene, char **info)
{
	t_vec3	*u;

	if (scene->camera)
		return (ft_pstderr(__ERR_3), 0);
	if (ft_tab_size(info) != 4)
		return (ft_pstderr(__ERR_4), 0);
	scene->camera = malloc(sizeof(t_camera));
	if (!scene->camera)
		return (ft_pstderr(__ERR_2), 0);
	u = ft_vec3_new(info[1]);
	if (!u)
		return (0);
	scene->camera->position = *u;
	(free(u), u = ft_vec3_new(info[2]));
	if (!u)
		return (0);
	scene->camera->orientation = *u;
	if (u->x < -1.0 || u->y < -1.0 || u->z < -1.0
		|| u->x > 1.0 || u->y > 1.0 || u->z > 1.0)
		return (ft_pstderr(__ERR_10), free(u), 0);
	free(u);
	scene->camera->fov = ft_atoi(info[3]);
	if (scene->camera->fov < 0 || scene->camera->fov > 180)
		return (ft_pstderr(__ERR_11), 0);
	return (1);
}

static uint8_t	ft_info_read(char **info, t_scene *scene)
{
	if (!info)
		return (0);
	if (!info[0])
		return (1);
	if (!ft_strncmp(info[0], "A", 2))
		return (ft_ambiance_init(scene, info));
	if (!ft_strncmp(info[0], "C", 2))
		return (ft_camera_init(scene, info));
	if (!ft_strncmp(info[0], "L", 2))
		return (ft_light_add(scene, info));
	return (ft_shape_add(scene, info));
}

static uint8_t	ft_scene_setup(t_scene *scene, const int fd)
{
	char	*line;
	char	**info;

	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		info = ft_split(line, ' ');
		if (!ft_info_read(info, scene))
		{
			while (line)
				(free(line), line = get_next_line(fd));
			if (!info)
				return (ft_pstderr(__ERR_2), 0);
			return (ft_tab_free(info), 0);
		}
		free(line);
		line = get_next_line(fd);
		ft_tab_free(info);
	}
	return (1);
}

t_scene	*ft_scene_new(char *file)
{
	t_scene	*scene;
	int		fd;
	uint8_t	ready;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (ft_pstderr(__ERR_2), NULL);
	scene->ambiance = NULL;
	scene->camera = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_perror(file), ft_scene_free(scene), NULL);
	ready = ft_scene_setup(scene, fd);
	if (close(fd) == -1)
		return (ft_perror(file), ft_scene_free(scene), NULL);
	if (!ready)
		return (ft_scene_free(scene), NULL);
	return (scene);
}
