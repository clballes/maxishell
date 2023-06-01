NAME = minishell
MAKE = make --no-print-directory
CC = gcc
LIBFT_DIR = libft
CFLAGS = -Wall -Wextra -Werror -g
INC_DIR = inc
OBJ_DIR = obj/
SRC_DIR = src/
BUILTINS_DIR = builtins/
HEREDOC_DIR = heredoc/
INTERACTIVE_DIR = interactive/
PARSING_DIR = parsing/
RM = rm -f
# FSANITIZE	:= -fsanitize=address


SRC_FILES	= main pipes $(HEREDOC_DIR)heredoc utils_minishell free $(BUILTINS_DIR)echo write_error $(BUILTINS_DIR)cd $(BUILTINS_DIR)env $(BUILTINS_DIR)utils_env $(BUILTINS_DIR)export/export $(BUILTINS_DIR)export/export_clean $(BUILTINS_DIR)export/utils_export $(BUILTINS_DIR)pwd $(BUILTINS_DIR)exit $(BUILTINS_DIR)unset path
SRC_FILES	+= 	$(PARSING_DIR)parsing_clean_input \
				$(PARSING_DIR)parsing_clean_input2 \
				$(PARSING_DIR)parsing_create_list_pipes \
				$(PARSING_DIR)parse_and_split \
				$(PARSING_DIR)parse_dolar_and_quottes \
				$(PARSING_DIR)parse_dolar_exp_utils \
				$(PARSING_DIR)parse_dolar_exp_utils2 \
				$(PARSING_DIR)parse_quottes \
				$(PARSING_DIR)parsing_redir_syntax \
				init


SRC_FILES	+= $(INTERACTIVE_DIR)signal 

SRC 		= 	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
DEPS 		= 	$(addprefix $(OBJ_DIR), $(addsuffix .d, $(SRC_FILES)))

RL_DIR := ${HOME}/.brew/opt/readline/

RL_LIB = -L$(RL_DIR)lib
RL_INCDIR = -I$(RL_DIR)include/readline

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
		mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)
		mkdir -p $(OBJ_DIR)$(INTERACTIVE_DIR)
		mkdir -p $(OBJ_DIR)$(HEREDOC_DIR)
		mkdir -p $(OBJ_DIR)$(BUILTINS_DIR)export/
		mkdir -p $(OBJ_DIR)$(PARSING_DIR) 
		$(CC)   -c $(CFLAGS) -MMD -I $(INC_DIR)  $< -o $@

all: makelibft
	 @$(MAKE) $(NAME)

makelibft:
		@$(MAKE) -C $(LIBFT_DIR)

bonus:
		@$(MAKE) all

-include $(DEPS)
$(NAME) : $(LIBFT_DIR)/libft.a $(OBJ) Makefile
		make -sC $(LIBFT_DIR)
		$(CC) $(CFLAGS)  $(FSANITIZE) $(OBJ) -o $(NAME) $(RL_INCDIR) $(RL_LIB) -lreadline -lhistory $(LIBFT_DIR)/libft.a

clean:
		$(RM) -r $(OBJ_DIR) $(DEPS)
		$(RM) $(LIBFT_DIR)/libft.a
		@make clean -C $(LIBFT_DIR)

fclean: clean
		$(RM) $(NAME)

re: fclean all

.PHONY : all clean re fclean makelibft
