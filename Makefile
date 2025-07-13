NAME = minishell

SRCDIR = src
LIBDIR = lib
LIBFTDIR = $(LIBDIR)/libft
OBJDIR = obj

SRCS = main.c env_utils.c env_memory.c env_operations.c env_init.c \
       token_utils.c token_memory.c token_operations.c \
       shell_core.c syntax_validator.c syntax_utils.c \
       expansion_utils.c lexer_utils.c lexer.c quote_handler.c \
       token_classifier.c pipeline_parser.c

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)

LIBFT = $(LIBFTDIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I$(LIBDIR)

GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(YELLOW)Linking $(NAME)...$(NC)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
	@echo "$(GREEN)$(NAME) compiled successfully!$(NC)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(OBJDIR)
	@echo "$(YELLOW)Compiling $<...$(NC)"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	@echo "$(YELLOW)Building libft...$(NC)"
	@$(MAKE) -C $(LIBFTDIR)
	@echo "$(GREEN)libft built successfully!$(NC)"

clean:
	@echo "$(RED)Cleaning object files...$(NC)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	@echo "$(RED)Cleaning $(NAME)...$(NC)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re run debug

