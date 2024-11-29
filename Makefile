SRCS			= $(shell find src -name "*.c")
OBJS_DIR		= obj/
OBJS 			= $(addprefix $(OBJS_DIR), $(SRCS:.c=.o))
INCS_DIR		= include/
INCS			= $(INCS_DIR)cub.h $(INCS_DIR)types.h
LIBFT_DIR		= lib/libft/
MLX_DIR			= lib/MLX42/
LIBFT			= $(LIBFT_DIR)libft.a
MLX				= $(MLX_DIR)build/libmlx42.a
CFLAGS			= -I$(INCS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)include/MLX42
CFLAGS			+= -Wall -Werror -Wextra -g -fsanitize=address
NAME			= cub3D
RM				= rm -rf
all:			$(NAME)

$(NAME) : $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -framework Cocoa -framework OpenGL -framework IOKit  -lglfw3 -L"/Users/$(USER)/.brew/opt/glfw/lib/" $(MLX) -o $(NAME)

$(OBJS_DIR)%.o : %.c $(INCS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT) :
	@make -C $(LIBFT_DIR) && make clean -C $(LIBFT_DIR)

clean :
	@$(RM) $(OBJS_DIR)

fclean : clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re : fclean all