# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abenamar <abenamar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/28 18:35:02 by abenamar          #+#    #+#              #
#    Updated: 2024/01/20 14:51:52 by abenamar         ###   ########.fr        #
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

SRCS += ft_tab_free.c
SRCS += ft_tab_size.c

# **************************************************************************** #
#                                                                              #
#                                     math                                     #
#                                                                              #
# **************************************************************************** #

SRCS += ft_atof.c

SRCS += ft_vec3_init.c

# **************************************************************************** #
#                                                                              #
#                                    scene                                     #
#                                                                              #
# **************************************************************************** #

SRCS += ft_color_init.c

SRCS += ft_ambiance_init.c
SRCS += ft_camera_init.c
SRCS += ft_light_add.c
SRCS += ft_shape_add.c

SRCS += ft_scene_free.c
SRCS += ft_scene_new.c

# **************************************************************************** #
#                                                                              #
#                                    render                                    #
#                                                                              #
# **************************************************************************** #

SRCS += ft_xsettings_reset.c
SRCS += ft_ximage_init.c
SRCS += ft_xclient_free.c
SRCS += ft_xclient_new.c

SRCS += ft_pixel_put.c
SRCS += ft_frame_render.c

SRCS += ft_key_press_handle.c

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