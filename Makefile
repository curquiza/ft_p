LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_H = $(LIBFT_DIR)/include

PROJECT_FOLDER_1 = ftp_server
PROJECT_FOLDER_2 = ftp_client

################################################################################
#################################### RULES #####################################
################################################################################

all : $(LIBFT)
	@printf "\033[1;33m%s\033[0m\n" "SERVER"
	@make -C $(PROJECT_FOLDER_1)
	@printf "\033[1;33m%s\033[0m\n" "CLIENT"
	@make -C $(PROJECT_FOLDER_2)

$(LIBFT) :
	@make -C $(LIBFT_DIR)
	@printf "%-45s\033[1;32m%s\033[0m\n" "Make $@" "OK"

clean :
	@make -C $(PROJECT_FOLDER_1) clean
	@make -C $(PROJECT_FOLDER_2) clean

fclean : clean
	@make -C $(PROJECT_FOLDER_1) fclean
	@make -C $(PROJECT_FOLDER_2) fclean

fclean_lib :
	@make fclean -C $(LIBFT_DIR)

fclean_all : fclean_lib fclean

re : fclean all

re_with_lib: fclean_all all
