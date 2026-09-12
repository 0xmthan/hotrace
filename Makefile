
NAME = hotrace
CC = cc
# -O3 optimizasyonu hızın puanlandığı bu projede kritik öneme sahiptir.
CFLAGS = -Wall -Wextra -Werror -O3

SRC_PATH = ./srcs/
OBJ_PATH = ./objects/
INC_PATH = ./includes/

# hotrace kaynak dosyalarınızı buraya ekleyin
SRC = main.c \
      hash_table.c \
      utils.c

SRCS = $(addprefix $(SRC_PATH), $(SRC))    
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I $(INC_PATH)

MAKEFLAGS += --silent

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	echo "🔷 Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS)
	echo "✅ Building $(NAME)..."
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(INC)

clean:
	echo "🧹 Cleaning object files..."
	rm -rf $(OBJ_PATH)
	echo "✅ Cleaning completed!"

fclean: clean
	echo "🧹 Full cleaning is in progress..."
	rm -f $(NAME)
	echo "✅ Full cleaning completed!"

re: fclean all

.PHONY: all clean fclean re