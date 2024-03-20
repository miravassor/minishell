# https://misc.flogisoft.com/bash/tip_colors_and_formatting
_BOLD      =\e[1m

# RESET list
_R          =\e[0m

# Colors
_RED      =\e[91m
_GREEN    =\e[92m
_YELLOW   =\e[93m
_BLUE     =\e[94m
_MAGENTA  =\e[35m
_CYAN     =\e[96m
_WHITE    =\e[97m





NAME											= minishell
EXEC											= $(NAME)

# *********************** DIRECTORY ************************************* #
SRC_DIR											= ./src/
OBJ_DIR											= obj/
INC												= -I ./inc/

# *********************** SOURCES **************************************** #
SRCS											= $(shell find $(SRC_DIR) -type d)
SRC												= minishell.c		\
													lexer.c			\
													token.c			\
													tree.c			\
													parse_utils.c	\
													exec.c			\
													exec_env.c		\
													exec_utils_1.c	\
													exec_utils_2.c	\
													exec_utils_3.c	\
													exec_error.c	\
													fds.c			\
													token_2.c		\
													token_utils_1.c	\
													token_utils_2.c	\
													tree_utils_1.c	\
													tree_utils_2.c	\
													tree_utils_3.c	\
													rror.c			\
													cleanr_1.c		\
													cleanr_2.c		\
													cd.c			\
													pwd.c			\
													exit.c			\
													exec_builtin.c	\
													pars_builtin.c	\
													echo.c			\
													env.c			\
													unset.c			\
													expandr_1.c		\
													expandr_2.c		\
													syntaxr.c		\
													exec_redir.c	\
													builtin_utils_1.c	\
													builtin_utils_2.c	\
													clear_empty.c	\
													unquote.c		\
													interpretr.c	\
													interpretr_2.c	\
													cleanr_3.c		\
													tree_utils_4.c	\
													syntaxr_utils.c	\
													clear_empty_2.c	\
													interpretr_3.c	\
													build_env.c		\
													export.c		\
													export_2.c		\
													gnl_add.c		\
													get_next_line_bonus.c \
													get_next_line_utils_bonus.c	\
													files.c			\
													sig_1.c			\
													sig_2.c			\
													group_cmd.c		\
													group_redir.c	\
													expandr_3.c		\
													here_doc.c		\
													chk_fnl.c		\
													cleanr_4.c		\
													empty_varg.c


# *********************** OBJECT ***************************************** #

OBJS											= $(addprefix $(OBJ_DIR), $(SRC:%.c=%.o))
vpath %.c $(SRCS)

$(OBJ_DIR)%.o									: 	%.c
													@mkdir -p $(OBJ_DIR)
													@$(CC) $(CFLAGS) -c $< -o $@

# *********************** COMPILATION ************************************ #
CC												= cc

$(EXEC)											: libft/libft.a $(OBJS)
													@$(CC) $(CFLAGS) -L/usr/local/lib -I/usr/local/include $(INC) $(OBJS) -L libft -lft -o $(EXEC) -lreadline
													@printf "$(_RED)$(_BOLD)Compiled : $(_WHITE)$(EXEC)$(_R)\n\n"
													@printf "$(_BOLD)$(_GREEN)................. Compilation succed .................$(_R)\n\n"


# ********************** FLAGS ******************************************* #
DEBUG											= 
CFLAGS											= -Wall -Wextra -Werror $(DEBUG) #fsanitize=adress -fsanitize=undefined

all												: header $(EXEC)

run												: $(EXEC)
													@./minishell

libft/libft.a									:
													@make -C libft
													@printf "$(_RED)$(_BOLD)Compiled : $(_WHITE)Libft$(_R)\n"

clean											:
													@rm -rf $(OBJ_DIR)
													make clean -C libft
													@printf "\n$(_MAGENTA)Removed : $(_WHITE)./$(OBJ_DIR)\n"

fclean											: clean
													@rm -f $(EXEC)
													@make fclean -C libft
													@printf "$(_MAGENTA)Removed : $(_WHITE)./$(EXEC)\n"
													@printf "$(_MAGENTA)Removed : $(_WHITE)./$(OBJ_DIR)\n\n"
													@printf "$(_GREEN)All is clean now !\n$(_R)"


valgrind										: $(EXEC)
# --show-reachable=yes --leak-check=full --show-leak-kinds=all
													@valgrind --log-file=output_valgrind --track-origins=yes --track-fds=yes ./$(EXEC)
													@printf "$(_BOLD)$(_CYAN)..........................................................$(_R)\n"
													@printf "$(_BOLD)$(_CYAN)..................  $(_MAGENTA)Valgrinds$(_CYAN)  ..................$(_R)\n"
													@printf "$(_BOLD)$(_CYAN)..........................................................$(_R)\n"
													@cat output_valgrind

re												: fclean
													@make all

header											:
												@printf "	$(_MAGENTA)#################################################################\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)___            ___    _____    _____        ___     _____  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|  '          '  |    |   |    |    '      |   |    |   |  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|   '        '   |    |   |    |     '     |   |    |   |  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|    '______'    |    |   |    |      '    |   |    |   |  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|                |    |   |    |       '   |   |    |   |  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|    ________    |    |   |    |   |'   '  |   |    |   |  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|    |      |    |    |   |    |   | '   '_|   |    |   |  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|    |      |    |    |   |    |   |  '        |    |   |  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##  $(_CYAN)$(_BOLD)|____|      |____|    |___|    |___|   '_______|    |___|  $(_MAGENTA)##\n"
												@printf "	$(_MAGENTA)##                                                             ##$(_R)\n"
												@printf "	$(_MAGENTA)##                      $(_WHITE)slorion / avassor  $(_MAGENTA)                    ##$(_R)\n"
												@printf "	$(_MAGENTA)##                                                             ##$(_R)\n"
												@printf "	$(_MAGENTA)#################################################################$(_R)\n"

.PHONY											= all run valgrind clean fclean re
