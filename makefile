NAME = rush02
SRCS = main.c ft_dict.c ft_convert.c
FLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	cc $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
