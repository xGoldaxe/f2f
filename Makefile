SRC = main.c \
my_mlx_pixel_put.c \
colors.c \
render_next_frame.c \
print_line.c \
utils.c \
parsing.c \
projection.c \
put_square.c \

CC = gcc

HEADER = fdf.h libft/libft.h

OBJ = $(SRC:%.c=./.build/%.o)

NAME = fdf

RM = rm -rf

LIBC = ar -rc

CFLAGS = -Wall -Wextra -Werror

LIBFT = @printf "\n\t\t${B_CYAN}GENERATE libft library ...\n\n${NONE}" && cd libft && make bonus

# COLORS
NONE			= \033[0m
CL_LINE			= \033[2K
B_RED			= \033[1;31m
B_GREEN			= \033[1;32m
B_MAGENTA 		= \033[1;35m
B_CYAN 			= \033[1;36m

./.build/%.o : %.c
	@$(CC) ${CFLAGS} -I. -o $@ -c $?
	@printf "${B_MAGENTA}Compilling $? ...\n${NONE}"

all :	
	@mkdir -p .build
	@make ${NAME}

${NAME} : $(OBJ)
	${LIBFT}
	@${CC} -o ${NAME} -I /usr/local/include/mlx.h ${OBJ} ./libft/libft.a -L \
	/usr/local/lib/ -lmlx -framework OpenGl -framework Appkit
	@printf "${B_GREEN}==>{${NAME}} LINKED SUCCESFULLY<==${NONE}\n"

clean :
	@${RM} .build
	@printf "${B_RED}XX{${NAME}} CLEANED SUCCESFULLY XX${NONE}\n"

fclean :	clean
	@cd libft && make fclean
	@${RM} ${NAME}
	@printf "${B_RED}XX{${NAME}} FCLEAN SUCCESFULL XX${NONE}\n"

re :	fclean all