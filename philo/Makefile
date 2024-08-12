NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread
RM = rm -rf

SRCDIR = src
OBJDIR = obj

SRCFILES = checking.c main.c philosophers_day.c utils.c check_filday.c action.c initialization.c
SRCS = $(addprefix $(SRCDIR)/, $(SRCFILES))

OBJS = $(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
