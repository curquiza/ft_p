NAME = client

FLAG = -Wall -Wextra -Werror
CC = gcc $(FLAG)

SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/, \
		misc.c \
		misc_arg_check.c \
		options.c \
		connect_to_server.c \
		communicate_with_server.c \
		quit_cmd.c \
		cd_cmd.c \
		ls_cmd.c \
		help_cmd.c \
		mode_cmd.c \
		pass_cmd.c \
		pwd_cmd.c \
		signal.c \
		send.c \
		reply_parser.c \
		etablish_data_connection.c \
		data_connection_active.c \
		data_connection_active_server_socket.c \
		data_connection_passive.c \
		data_connecton_passive_get_args.c \
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
