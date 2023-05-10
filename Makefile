NAME = minishell
MAKE = make --no-print-directory
CC = gcc
LIBFT_DIR = libft
CFLAGS = -Wall -Wextra -Werror -g
INC_DIR = inc
OBJ_DIR = obj/
SRC_DIR = src/
BUILTINS_DIR = builtins/
PARSING_DIR = parsing/
RM = rm -f
# FSANITIZE	:= -fsanitize=address -g3

SRC_FILES	= main utils_minishell free $(BUILTINS_DIR)echo $(BUILTINS_DIR)cd $(BUILTINS_DIR)env $(BUILTINS_DIR)utils_env $(BUILTINS_DIR)export/export $(BUILTINS_DIR)export/export_clean $(BUILTINS_DIR)export/utils_export $(BUILTINS_DIR)pwd $(BUILTINS_DIR)exit
SRC_FILES	+= $(PARSING_DIR)parsing_clean_input $(PARSING_DIR)parsing_pipes_commands $(PARSING_DIR)parse_and_split $(PARSING_DIR)parse_dolar_exp init

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)
		mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)export/
		mkdir -p $(OBJ_DIR)$(PARSING_DIR) 
		$(CC)   -c $(CFLAGS) -MMD -I $(INC_DIR) $< -o $@

all: makelibft
	 @$(MAKE) $(NAME)

makelibft:
		@$(MAKE) -C $(LIBFT_DIR)

bonus:
		@$(MAKE) all

-include $(DEPS)
$(NAME) : $(LIBFT_DIR)/libft.a $(OBJ) Makefile
		make -sC $(LIBFT_DIR)
		$(CC) $(CFLAGS)  $(FSANITIZE) $(OBJ) -o $(NAME) -lreadline $(LIBFT_DIR)/libft.a

clean:
		$(RM) -r $(OBJ_DIR) $(DEPS)
		$(RM) $(LIBFT_DIR)/libft.a
		@make clean -C $(LIBFT_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY : all clean re fclean makelibft
