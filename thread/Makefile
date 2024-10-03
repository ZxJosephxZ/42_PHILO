
SRC = main.c lista.c time.c  philo_utils.c \
	 lista_utils.c pars_number.c pars_string.c
NAME = filosofos
CFLAGS = -Wall -Wextra -Werror -pthread
CC = gcc
RM = rm -f
PRINTF = printf
DIC_SRC = thread
DIC_OBJ = obj
DIC_BIN = bin
OBJ = $(addprefix $(DIC_OBJ)/, $(SRC:.c=.o))

all : $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@
	@$(PRINTF) "PROCESO TERMINADO o.o\n"

$(DIC_OBJ)/%.o:  %.c | $(DIC_OBJ)
	@$(CC) -c $< -o $@

$(DIC_OBJ):
	@mkdir -p $(DIC_OBJ)

clean: 
	@$(RM) -r $(DIC_OBJ)
	$(PRINTF) "objetos eliminados\n"

fclean: clean
	@$(RM) $(NAME)

re: fclean
	@make all
