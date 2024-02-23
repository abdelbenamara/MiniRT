# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:35:02 by abenamar          #+#    #+#              #
#    Updated: 2024/02/23 20:37:19 by abenamar         ###   ########.fr        #
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

SRCS := ft_pstderr.c
SRCS += ft_perror.c

SRCS += ft_tab_free.c
SRCS += ft_tab_size.c

# **************************************************************************** #
#                                                                              #
#                                     math                                     #
#                                                                              #
# **************************************************************************** #

SRCS += ft_atof.c

SRCS += ft_vec3_new.c
SRCS += ft_vec3.c
SRCS += ft_vec3_sum.c
SRCS += ft_vec3_diff.c
SRCS += ft_vec3_prod.c
SRCS += ft_vec3_length_squared.c
SRCS += ft_vec3_length.c
SRCS += ft_vec3_unit.c
SRCS += ft_vec3_dot.c
SRCS += ft_vec3_cross.c

SRCS += ft_ray.c

SRCS += ft_interval.c

# **************************************************************************** #
#                                                                              #
#                                    scene                                     #
#                                                                              #
# **************************************************************************** #

SRCS += ft_color_read.c
SRCS += ft_color_build.c

SRCS += ft_light_add.c
SRCS += ft_shape_add.c

SRCS += ft_scene_free.c
SRCS += ft_scene_new.c
SRCS += ft_scene_hit.c

SRCS += ft_viewport.c

# **************************************************************************** #
#                                                                              #
#                                    render                                    #
#                                                                              #
# **************************************************************************** #

SRCS += ft_xclient_free.c
SRCS += ft_xclient_new.c
SRCS += ft_xclient_buffer.c
SRCS += ft_xclient_flush.c

SRCS += ft_pixel_put.c
SRCS += ft_ray_tracing.c
SRCS += ft_key_press.c

SRCS += miniRT.c

OBJS := $(SRCS:.c=.o)

BOBJS := $(BSRCS:.c=.o)

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