
# CPPFLAGS = -I/Users/fstitou/.brew/opt/readline/inlclude
# LDFLAGS = -L/Users/fstitou/.brew/opt/readline/lib
CPPFLAGS = -I/goinfre/fstitou/homebrew/opt/readline/include
LDFLAGS = -L/goinfre/fstitou/homebrew/opt/readline/lib

NAME = minishell
NAME_BONUS = 

SRC = minishell.c lexer.c signals.c tokenizing.c utils.c utils2.c execute.c parse_utils.c builtins.c split.c\
		export-env.c export-env-utils.c cd.c echo.c env.c execute_utils.c exit.c export.c pwd.c unset.c\
		redirections.c here_doc.c utils_func.c parsing_utils.c funct.c lexer_utils.c lexer_utils1.c path.c\
		parse.c redir_helper.c utils_funct1.c\

		
SRC_BONUS = 


OBJ = minishell.o lexer.o signals.o tokenizing.o utils.o utils2.o execute.o parse_utils.o builtins.o split.o\
		export-env.o export-env-utils.o cd.o echo.o env.o execute_utils.o exit.o export.o pwd.o unset.o\
		redirections.o here_doc.o utils_func.o parsing_utils.o funct.o lexer_utils.o lexer_utils1.o path.o\
		parse.o redir_helper.o utils_funct1.o\

OBJ_BONUS = 


all : $(NAME)

$(NAME):
	
	@gcc  -Wall -Wextra -Werror $(SRC) $(LDFLAGS) $(CPPFLAGS) -lreadline  -o $(NAME)
	@echo "Mino 👍👍👍"

$(NAME_BONUS) : 
	@gcc -Wall -Wextra -Werror -g $(SRC_BONUS) -o $(NAME_BONUS)
	@echo "🎁🎁🎁"

bonus: $(NAME_BONUS)

clean :
 
	@rm -f $(OBJ) $(OBJ_BONUS)
	@echo "🚮🚮🚮"

fclean : clean
	@rm -f $(NAME) $(NAME_BONUS)
	@echo "🗑️ 🗑️ 🗑️"

re : fclean all