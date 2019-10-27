NAME = server

FLAG = -Wall -Wextra -Werror
CC = gcc $(FLAG)

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
		options.c \
		display_logs.c \
		display_logs2.c \
		misc.c \
		misc_chunk_list.c \
		signal.c \
		close_connection.c \
		communicate_with_new_user.c \
		listen_to_clients.c \
		exec_retr_cmd_send_file.c \
		exec_retr_cmd.c \
		exec_stor_cmd.c \
		exec_pasv_cmd.c \
		exec_epsv_cmd_accept.c \
		exec_epsv_cmd.c \
		exec_list_cmd.c \
		exec_port_cmd_arg_tab.c \
		exec_port_cmd.c \
		exec_eprt_cmd.c \
		exec_pwd_cmd.c \
		exec_type_cmd.c \
		exec_cwd_cmd.c \
		get_file_content.c \
		bind_server.c \
		path_access.c \
		send.c \
		create_main_server_socket.c \
		main.c)

OBJ_DIR = obj
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

LIBFT_DIR = ../libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/include

H_DIR = include
INCL = -I$(H_DIR) -I$(LIBFT_H)


################################################################################
#################################### RULES #####################################
################################################################################

all : $(NAME)

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(NAME) : $(LIBFT) $(OBJ)
	@$(CC) $(OBJ) -o $@ $(LIBFT)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(H_DIR)
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(INCL) -c $< -o $@
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@rm -rf $(OBJ_DIR)

fclean : clean
	@rm -f $(NAME)

fclean_lib :
	@make fclean -C $(LIBFT_DIR)

fclean_all : fclean_lib fclean

re : fclean all

re_with_lib: fclean_all all
