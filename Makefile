NAME = philo
FLAGS = -Wall -Wextra -Werror -pthread -g -gdwarf-4

SRC = philosopher.c\
		init_table.c\
		init_philo.c\
		ft_life.c\
		ft_death.c\
		utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Compiling..."
	@gcc $(FLAGS) -o $(NAME) $(OBJ)
	@echo "Done!"
	@echo "Executable: $(NAME)"

%.o: %.c
	@echo "Compiling $<..."
	@gcc $(FLAGS) -c $< -o $@
	@echo "Done!"

clean:
	@echo "Cleaning up..."
	@rm -f $(OBJ)
	@echo "Done!"

fclean: clean
	@echo "Removing executable..."
	@rm -f $(NAME)
	@echo "Done!"
re: fclean all

.PHONY: all clean fclean re