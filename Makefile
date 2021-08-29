NAME = pipex

NAME_B = 

MAC = 

MAC_B = 

LIBFT = libft

FLAGS 	= -Wall -Wextra  #-framework OpenGL -framework AppKit libft.a -glldb
 
SRCS =  	path_env.c							\
			init_cmd.c							\
			main_test_start.c					\
			utils.c

SRCS_BONUS =	 

CC 		= gcc
OBJ 	= ${SRCS:.c=.o}
OBJS 	= *.o
OBJ_B = ${SRCS_BONUS:.c=.o}
OBJS_B = *.o
 
.c.o:
	${CC} ${FLAGS} -c $< -o ${<:.c=.o}
 
all : 
	@make -C $(LIBFT)
	@make $(NAME)

$(NAME)	: $(OBJ) 
	$(CC) $(FLAGS) -I libft/includes/  $(OBJ) libft/libft.a -o $(NAME)
 
$(NAME_B) : $(OBJ_B)
	$(CC) $(FLAGS) -I libft/includes/  $(OBJ_B) libft/libft.a -o $(NAME_B)

clean : 
		@make clean -C $(LIBFT)
		@rm -rf $(OBJ)
		@rm -rf $(OBJ_B)
 
fclean : clean
		@make fclean -C $(LIBFT)
		@rm -rf $(OBJS)
		@rm -rf $(OBJS_B)
		@rm -rf $(NAME)
		@rm -rf $(NAME_B)
 
relinux : fclean LINUX
 
re : fclean all
	
 
 
bonus : 
		@make -C $(LIBFT)
		@make ${NAME_B}
 
rebonus : fclean bonus
