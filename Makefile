NAME			= Minishell

CFLAGS			= -Wall -Wextra -Werror -g3 #-fsanitize=address

SRC				=	 \
					./srcs/builtins_error.c ./srcs/builtins_utils.c \
					./srcs/cd.c \
					./srcs/command.c \
					./srcs/env_var_utils.c ./srcs/env_var.c \
					./srcs/exec_end.c ./srcs/exec_utils.c ./srcs/exec.c \
					./srcs/exit.c \
					./srcs/export_error.c ./srcs/export_get_var.c ./srcs/export_printer.c ./srcs/export_utils.c ./srcs/export.c \
					./srcs/free_2.c ./srcs/free.c \
					./srcs/ft_print_prompt.c \
					./srcs/get_var_utils.c \
					./srcs/init.c \
					./srcs/quote.c \
					./srcs/redir_utils.c ./srcs/redir.c \
					./srcs/splitter_utils.c ./srcs/splitter.c \
					./srcs/unset.c ./srcs/utils_2.c ./srcs/utils.c \
					./dynamic_reader/ctrl.c \
					./dynamic_reader/get_next_line_utils.c ./dynamic_reader/get_next_line.c \
					./dynamic_reader/history.c \
					./dynamic_reader/key_2.c ./dynamic_reader/keys_utils.c ./dynamic_reader/keys.c \
					./dynamic_reader/main.c \
					./dynamic_reader/reader_utils.c ./dynamic_reader/reader.c \
					./dynamic_reader/utils.c \

ROAD_S			= $(SRC)

ROAD_O			= $(OBJ)

ROAD_B			= $(SRCB)


OBJ				= $(SRC:.c=.o)

CC				= clang

HEADER_DIR		=  -I./includes/minishell.h 

$(NAME) :		$(OBJ)
				@make -C libft
				@make -C ft_printf
				@mv libft/libft.a ./lib
				@mv ft_printf/libftprintf.a lib/
				$(CC) $(OBJ) lib/libftprintf.a lib/libft.a  -ltermcap -o $(NAME)

LIBFT			= libft

all :			$(NAME)

clean :
				@make -C libft clean
				@make -C ft_printf clean
				@rm -f $(ROAD_O)

fclean :
				@make -C libft fclean
				@make -C ft_printf fclean
				@rm -f lib/*.a
				@rm -f $(ROAD_O)
				@rm -f $(NAME)

re : 			fclean all

.PHONY: 		all clean fclean re
