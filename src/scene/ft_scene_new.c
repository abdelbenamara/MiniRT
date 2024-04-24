/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:00:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/24 04:01:14 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_ambiance_init(t_scene *const scene, char *const *info)
{
	float	lratio;

	if (scene->ambiance)
		return (ft_pstderr(__ERR_08), false);
	if (ft_tab_size(info) != 3)
		return (ft_pstderr(__ERR_09), false);
	scene->ambiance = malloc(sizeof(t_color3f));
	if (!scene->ambiance)
		return (ft_pstderr(__ERR_07), false);
	lratio = ft_str_to_float(info[1]);
	if (!isfinite(lratio))
		return (ft_pstderr(__ERR_09), false);
	if (signbit(lratio) || lratio > 1.0F)
		return (ft_pstderr(__ERR_11), false);
	*scene->ambiance = ft_str_to_color3f(info[2]);
	if (isnan(scene->ambiance->x))
		return (false);
	*scene->ambiance = ft_vec3f_prod(*scene->ambiance, lratio);
	return (true);
}

static bool	ft_element_setup(t_scene *const scene, char *const *info)
{
	static bool	(*ft_setup[])(t_scene *const, char *const *) = {
		ft_ambiance_init, ft_camera_init, ft_light_init,
		ft_sphere_add, ft_plane_add, ft_cylinder_add
	};
	int			id;

	if (!info)
		return (false);
	if (!info[0] || info[0][0] == '#')
		return (true);
	id = !ft_strncmp(info[0], "A", 2) \
		+ 2 * !ft_strncmp(info[0], "C", 2) \
		+ 3 * !ft_strncmp(info[0], "L", 2) \
		+ 4 * !ft_strncmp(info[0], "sp", 3) \
		+ 5 * !ft_strncmp(info[0], "pl", 3) \
		+ 6 * !ft_strncmp(info[0], "cy", 3);
	if (!id)
		return (ft_pstderr(__ERR_18), false);
	if (!ft_setup[id - 1](scene, info))
		return (false);
	return (true);
}

static bool	ft_scene_setup(t_scene *const scene, int const fd)
{
	char	*line;
	char	**info;

	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		info = ft_split(line, ' ');
		if (!ft_element_setup(scene, info))
		{
			while (line)
				(free(line), line = get_next_line(fd));
			if (!info)
				return (ft_pstderr(__ERR_07), false);
			return (ft_tab_free(info), false);
		}
		free(line);
		line = get_next_line(fd);
		ft_tab_free(info);
	}
	if (scene->ambiance == NULL
		|| scene->camera == NULL
		|| scene->light == NULL)
		return (ft_pstderr(__ERR_20), false);
	return (true);
}

t_scene	*ft_scene_new(char const *file)
{
	t_scene	*scene;
	int		fd;
	bool	ready;

	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (ft_pstderr(__ERR_07), NULL);
	scene->ambiance = NULL;
	scene->camera = NULL;
	scene->light = NULL;
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
	scene->focus.type = 0;
	scene->focus.next = NULL;
	ft_focus_camera(scene);
	return (scene);
}
