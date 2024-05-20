#################################################
## COLORS
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
END = \033[0m

#################################################
## ARGUMENTS

NAME				= pipex
CFLAGS				= -Wall -Werror -Wextra -g3
CC					= cc
LIBFT				= libft
BUILD				= objs/
INCLUDE				= pipex.h


#################################################
## SOURCES

SRC_FILES_1		=	main \

SRC_FILES_2		=	utils \
					error \
					exec \
					exec_utils \
					init_struct \
					my_strjoin \
					here_doc \

SRC_1			= 	$(addprefix srcs/, $(SRC_FILES_1))
SRC_2			= 	$(addprefix srcs/, $(SRC_FILES_2))


OBJ_FILES_1		= $(addprefix $(BUILD), $(addsuffix .o, $(SRC_FILES_1)))
OBJ_FILES_2		= $(addprefix $(BUILD), $(addsuffix .o, $(SRC_FILES_2)))

SRC_BONUS		=	main_bonus \

BONUS			= 	$(addprefix bonus/, $(SRC_BONUS))

OBJ_BONUS		= $(addprefix $(BUILD), $(addsuffix .o, $(SRC_BONUS)))


#################################################
## RULES

${NAME} : ${OBJ_FILES_1} ${OBJ_FILES_2} $(INCLUDES)
	@make --silent -C $(LIBFT)
	@${CC} ${CFLAGS} ${OBJ_FILES_1} ${OBJ_FILES_2} -L $(LIBFT) -lft -o ${NAME}
	@echo "$(GREEN)Compilation done!$(END)"

bonus: ${OBJ_BONUS} ${OBJ_FILES_2} $(INCLUDES)
	@make --silent -C $(LIBFT)
	@${CC} ${CFLAGS} ${OBJ_BONUS} ${OBJ_FILES_2} -L $(LIBFT) -lft -o ${NAME}
	@echo "$(GREEN)Compilation bonus done!$(END)"

objs/%.o: srcs/%.c
	@mkdir -p ${BUILD}
	@${CC} ${CFLAGS} -c $< -o $@

objs/%.o: bonus/%.c
	@mkdir -p ${BUILD}
	@${CC} ${CFLAGS} -c $< -o $@

all : ${NAME}

clean :
	@rm -rf $(BUILD)*.o
	@make clean --silent -C $(LIBFT)
	clear
	@echo "$(CYAN)All clean !$(END)"

fclean : clean
	@rm -f ${NAME}
	@make fclean --silent -C $(LIBFT)
	@echo "$(CYAN)All clean !$(END)"

re : fclean all

.PHONY : all clean fclean re bonus