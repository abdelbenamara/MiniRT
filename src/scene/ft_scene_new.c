/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:00:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/04/01 19:18:05 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static bool	ft_element_setup(t_scene *const scene, char *const *info)
{
	static bool	(*ft_setup[])(t_scene *const, char *const *) = {
		ft_ambiance_init, ft_camera_init, ft_light_add,
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
		return (ft_pstderr(__ERR_13), false);
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
				return (ft_pstderr(__ERR_2), false);
			return (ft_tab_free(info), false);
		}
		free(line);
		line = get_next_line(fd);
		ft_tab_free(info);
	}
	if (scene->camera == NULL)
		return (ft_pstderr(__ERR_15), false);
	return (true);
}

t_scene	*ft_scene_new(char const *file)
{
	t_scene	*scene;
	int		fd;
	bool	ready;

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
