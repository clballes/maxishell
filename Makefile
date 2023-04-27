NAME = minishell
MAKE = make --no-print-directory
CC = gcc
LIBFT_DIR = libft
CFLAGS = -Wall -Wextra -Werror 
INC_DIR = inc
OBJ_DIR = obj/
SRC_DIR = src/
BUILTINS_DIR = builtins/
RM = rm -f
#FSANITIZE	:= -fsanitize=addresmas -g3

SRC_FILES	= main utils_minishell $(BUILTINS_DIR)echo $(BUILTINS_DIR)env free $(BUILTINS_DIR)utils_env $(BUILTINS_DIR)export $(BUILTINS_DIR)utils_export $(BUILTINS_DIR)pwd $(BUILTINS_DIR)exit

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)
		mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)
		$(CC) -I $(INC_DIR)  -c $(CFLAGS) -MMD $< -o $@

all: makelibft
	 @$(MAKE) $(NAME)

makelibft:
		@$(MAKE) -C $(LIBFT_DIR)

bonus:
		@$(MAKE) all

-include $(DEPS)
$(NAME) : $(LIBFT_DIR)/libft.a $(OBJ) Makefile
		make -sC $(LIBFT_DIR)
		$(CC) $(CFLAGS) -lreadline $(FSANITIZE) $(LIBFT_DIR)/libft.a $(OBJ) -o $(NAME)

clean:
		$(RM) -r $(OBJ_DIR) $(DEPS)
		$(RM) $(LIBFT_DIR)/libft.a
		@make clean -C $(LIBFT_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY : all clean re fclean makelibft
