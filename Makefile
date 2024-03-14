# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:35:02 by abenamar          #+#    #+#              #
#    Updated: 2024/03/14 16:57:16 by abenamar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := miniRT

LIBFT := $(CURDIR)/libft/libft.a

MLX := $(CURDIR)/mlx/libmlx.a

INCLUDES := -I $(CURDIR)
INCLUDES += -I $(CURDIR)/libft
INCLUDES += -I $(CURDIR)/mlx

LDFLAGS := -L$(CURDIR)/libft
LDFLAGS += -L$(CURDIR)/mlx

LDLIBS := -lft
LDLIBS += -lmlx
LDLIBS += -lXext
LDLIBS += -lX11
LDLIBS += -lm

# **************************************************************************** #
#                                                                              #
#                                    utils                                     #
#                                                                              #
# **************************************************************************** #

SRC_UTILS := src/utils

SRCS := $(SRC_UTILS)/ft_pstderr.c
SRCS += $(SRC_UTILS)/ft_perror.c

SRCS += $(SRC_UTILS)/ft_tab_free.c
SRCS += $(SRC_UTILS)/ft_tab_size.c

# **************************************************************************** #
#                                                                              #
#                                     math                                     #
#                                                                              #
# **************************************************************************** #

SRC_MATH := src/math

SRCS += $(SRC_MATH)/ft_atof.c

SRCS += $(SRC_MATH)/ft_vec3.c
SRCS += $(SRC_MATH)/ft_vec3_sum.c
SRCS += $(SRC_MATH)/ft_vec3_diff.c
SRCS += $(SRC_MATH)/ft_vec3_prod.c
SRCS += $(SRC_MATH)/ft_vec3_len.c
SRCS += $(SRC_MATH)/ft_vec3_unit.c
SRCS += $(SRC_MATH)/ft_vec3_dot.c
SRCS += $(SRC_MATH)/ft_vec3_cross.c
SRCS += $(SRC_MATH)/ft_vec3_rotate.c

# **************************************************************************** #
#                                                                              #
#                                    scene                                     #
#                                                                              #
# **************************************************************************** #

SRC_SCENE := src/scene

SRCS += $(SRC_SCENE)/ft_color_read.c
SRCS += $(SRC_SCENE)/ft_vec3_read.c
SRCS += $(SRC_SCENE)/ft_vec3_is_normalized.c

SRCS += $(SRC_SCENE)/ft_ambiance_init.c
SRCS += $(SRC_SCENE)/ft_camera_init.c
SRCS += $(SRC_SCENE)/ft_light_add.c
SRCS += $(SRC_SCENE)/ft_sphere_add.c
SRCS += $(SRC_SCENE)/ft_plane_add.c
SRCS += $(SRC_SCENE)/ft_cylinder_add.c
SRCS += $(SRC_SCENE)/ft_scene_free.c
SRCS += $(SRC_SCENE)/ft_scene_new.c

# **************************************************************************** #
#                                                                              #
#                                    render                                    #
#                                                                              #
# **************************************************************************** #

SRC_RENDER := src/render

SRCS += $(SRC_RENDER)/ft_xclient_free.c
SRCS += $(SRC_RENDER)/ft_xclient_new.c
SRCS += $(SRC_RENDER)/ft_xclient_buffer.c
SRCS += $(SRC_RENDER)/ft_xclient_flush.c

SRCS += $(SRC_RENDER)/ft_viewport.c
SRCS += $(SRC_RENDER)/ft_ray.c
SRCS += $(SRC_RENDER)/ft_cylinder_hit.c
SRCS += $(SRC_RENDER)/ft_scene_hit.c

SRCS += $(SRC_RENDER)/ft_pixel_color.c
SRCS += $(SRC_RENDER)/ft_pixel_put.c
SRCS += $(SRC_RENDER)/ft_ray_tracing.c
SRCS += $(SRC_RENDER)/ft_key_press.c

# **************************************************************************** #

SRCS += miniRT.c

OBJS := $(SRCS:.c=.o)

CC := cc

CFLAGS := -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

RM := rm -f

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

$(NAME): $(LIBFT) $(MLX) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES) $(LDFLAGS) $(LDLIBS)

$(LIBFT):
	@$(MAKE) -C $(CURDIR)/libft $(findstring bonus, $(MAKECMDGOALS))

$(MLX):
	@$(MAKE) -C $(CURDIR)/mlx

bonus: $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: re fclean clean all bonus