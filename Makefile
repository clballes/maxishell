NAME = minishell
MAKE = make --no-print-directory
CC = gcc
LIBFT_DIR = libft
CFLAGS = -Wall -Wextra -Werror -g
INC_DIR = inc -I/Users/albagarc/.brew/opt/readline/include/readline/
OBJ_DIR = obj/
SRC_DIR = src/
BUILTINS_DIR = builtins/
HEREDOC_DIR = heredoc/
INTERACTIVE_DIR = interactive/
PARSING_DIR = parsing/
REDIR_DIR = redirections/
RM = rm -f
# FSANITIZE	:= -fsanitize=address

SRC_FILES =		main \
				minishell_starts \
				minishell_starts_utils \
				utils_minishell \
				free \
				write_error \
				init \
				set_pipes \
				$(INTERACTIVE_DIR)signal \
				$(HEREDOC_DIR)heredoc \
				$(BUILTINS_DIR)shlvl \
				$(BUILTINS_DIR)echo \
				$(BUILTINS_DIR)cd \
				$(BUILTINS_DIR)env \
				$(BUILTINS_DIR)env_list_utils \
				$(BUILTINS_DIR)export/export \
				$(BUILTINS_DIR)export/export_clean \
				$(BUILTINS_DIR)export/utils_export \
				$(BUILTINS_DIR)pwd \
				$(BUILTINS_DIR)exit \
				$(BUILTINS_DIR)exit_utils \
				$(BUILTINS_DIR)unset path \
				$(PARSING_DIR)parsing_clean_input \
				$(PARSING_DIR)parsing_clean_input2 \
				$(PARSING_DIR)parsing_create_list_pipes \
				$(PARSING_DIR)parse_and_split \
				$(PARSING_DIR)parse_dolar_and_quottes \
				$(PARSING_DIR)parse_dolar_exp_utils \
				$(PARSING_DIR)parse_dolar_exp_utils2 \
				$(PARSING_DIR)parse_dolar_env_utils \
				$(PARSING_DIR)parse_quottes \
				$(PARSING_DIR)parsing_redir_syntax \
				$(PARSING_DIR)parsing_pipes_syntax \
				$(REDIR_DIR)redirections_create_list \
				$(REDIR_DIR)redirections_list_utils \
				$(REDIR_DIR)redirections_utils \
				$(REDIR_DIR)redirections \

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)
		mkdir -p $(OBJ_DIR)$(INTERACTIVE_DIR)
		mkdir -p $(OBJ_DIR)$(HEREDOC_DIR)
		mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)export/
		mkdir -p $(OBJ_DIR)$(PARSING_DIR) 
		mkdir -p $(OBJ_DIR)$(REDIR_DIR)
		$(CC)   -c $(CFLAGS) -MMD -I $(INC_DIR) -I/Users/$(USER)/.brew/opt/readline/include $< -o $@

all: makelibft
	 @$(MAKE) $(NAME)

makelibft:
		@$(MAKE) -C $(LIBFT_DIR)

bonus:
		@$(MAKE) all

$(NAME) : $(LIBFT_DIR)/libft.a $(OBJ) Makefile
		make -sC $(LIBFT_DIR)
		$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/libft.a -lreadline -lhistory -L/Users/$(USER)/.brew/opt/readline/lib  

-include $(DEPS)
clean:
		$(RM) -r $(OBJ_DIR) $(DEPS)
		$(RM) $(LIBFT_DIR)/libft.a
		@make clean -C $(LIBFT_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY : all clean re fclean makelibft