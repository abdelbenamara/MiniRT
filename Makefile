# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:35:02 by abenamar          #+#    #+#              #
#    Updated: 2024/04/01 01:13:10 by abenamar         ###   ########.fr        #
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

SRCS += $(SRC_MATH)/ft_vec3f.c
SRCS += $(SRC_MATH)/ft_vec3f_sum.c
SRCS += $(SRC_MATH)/ft_vec3f_diff.c
SRCS += $(SRC_MATH)/ft_vec3f_prod.c
SRCS += $(SRC_MATH)/ft_vec3f_unit.c
SRCS += $(SRC_MATH)/ft_vec3f_dot.c
SRCS += $(SRC_MATH)/ft_vec3f_cross.c

SRCS += $(SRC_MATH)/ft_quat4f.c
SRCS += $(SRC_MATH)/ft_quat4f_prod.c
SRCS += $(SRC_MATH)/ft_quat4f_unit.c

# **************************************************************************** #
#                                                                              #
#                                    scene                                     #
#                                                                              #
# **************************************************************************** #

SRC_SCENE := src/scene

SRCS += $(SRC_SCENE)/ft_color3f_read.c
SRCS += $(SRC_SCENE)/ft_vec3f_read.c
SRCS += $(SRC_SCENE)/ft_vec3f_isnormalized.c

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

SRCS += $(SRC_RENDER)/ft_ray.c
SRCS += $(SRC_RENDER)/ft_face_normal.c
SRCS += $(SRC_RENDER)/ft_sphere_hit.c
SRCS += $(SRC_RENDER)/ft_plane_hit.c
SRCS += $(SRC_RENDER)/ft_cylinder_hit.c

SRCS += $(SRC_RENDER)/ft_pixel_put.c
SRCS += $(SRC_RENDER)/ft_ray_tracing.c
SRCS += $(SRC_RENDER)/ft_basis.c
SRCS += $(SRC_RENDER)/ft_vec3f_rotate.c
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