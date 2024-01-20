/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_scene_new.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 11:00:24 by abenamar          #+#    #+#             */
/*   Updated: 2024/01/20 18:05:05 by abenamar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

uint8_t	ft_info_parse(char **info, t_scene *scene)
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

uint8_t	ft_scene_init(t_scene *scene, const int fd)
{
	char	*line;
	char	**info;

	line = get_next_line(fd);
	while (line)
	{
		line[ft_strlen(line) - 1] = '\0';
		info = ft_split(line, ' ');
		if (!ft_info_parse(info, scene))
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
	int		fd;
	t_scene	*scene;
	uint8_t	init;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (ft_perror(file), NULL);
	scene = malloc(sizeof(t_scene));
	if (!scene)
		return (ft_pstderr(__ERR_2), NULL);
	scene->ambiance = NULL;
	scene->camera = NULL;
	scene->lights = NULL;
	scene->spheres = NULL;
	scene->planes = NULL;
	scene->cylinders = NULL;
	init = ft_scene_init(scene, fd);
	if (close(fd) == -1)
		return (ft_perror(file), ft_scene_free(scene), NULL);
	if (!init)
		return (ft_scene_free(scene), NULL);
	return (scene);
}
