# SRCS  = tokenzation.c exec.c
# CC = cc
# CFLAGS = -Wall -Wextra -Werror
# NAME = minishell

# OBJS = $(SRCS:.c=.o)

# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a

# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) -L/Users/ouel-afi/goinfre/homebrew/opt/readline/lib -lreadline $(OBJS) $(LIBFT) -o $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)

# %.o: %.c 
# 	$(CC) $(CFLAGS) -I/Users/ouel-afi/goinfre/homebrew/opt/readline/include -c $< -o $@

# clean:
# 	rm -f $(OBJS) 
# 	$(MAKE) clean -C $(LIBFT_DIR)

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) fclean -C $(LIBFT_DIR)

# re: fclean all

# .PHONY: all bonus clean fclean re



# SRCS = checker.c checker2.c create_tree.c handle_word.c free2.c utils2.c  parser.c heredoc.c parser2.c tokenizer.c lexer.c handler.c exec.c ft_cd.c tree.c check_path.c main.c env_list.c ft_echo.c ft_export.c print.c ft_env.c ft_exit.c ft_unset.c ft_pwd.c utils.c env_list2.c free.c expand.c pipe.c redirections.c

# CC = cc
# CFLAGS = -Wall -Wextra -Werror  -I/home/linuxbrew/.linuxbrew/opt/readline/include
# LDFLAGS = -L/home/linuxbrew/.linuxbrew/opt/readline/lib -lreadline

# NAME = minishell
# OBJS = $(SRCS:.c=.o)

# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a

# all: $(NAME)

# $(NAME): $(OBJS) $(LIBFT)
# 	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(LDFLAGS) -o $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	rm -f $(OBJS)
# 	$(MAKE) clean -C $(LIBFT_DIR)

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) fclean -C $(LIBFT_DIR)

# re: fclean all

# .PHONY: all clean fclean re




SRCS =  checker.c checker2.c create_tree.c handle_word.c free2.c utils2.c parser.c heredoc.c parser2.c tokenizer.c lexer.c handler.c exec.c ft_cd.c tree.c  check_path.c main.c env_list.c ft_echo.c ft_export.c print.c ft_env.c ft_exit.c ft_unset.c ft_pwd.c utils.c env_list2.c free.c expand.c pipe.c redirections.c
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = minishell

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -L/Users/taya/goinfre/homebrew/opt/readline/lib -lreadline $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c 
	$(CC) $(CFLAGS) -I/Users/taya/goinfre/homebrew/opt/readline/include -c $< -o $@

clean:
	rm -f $(OBJS) 
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all bonus clean fclean re






# SRCS =  checker.c checker2.c create_tree.c handle_word.c free2.c utils2.c parser.c heredoc.c parser2.c tokenizer.c lexer.c handler.c exec.c ft_cd.c tree.c  check_path.c main.c env_list.c ft_echo.c ft_export.c print.c ft_env.c ft_exit.c ft_unset.c ft_pwd.c utils.c env_list2.c free.c expand.c pipe.c redirections.c
# CC = cc
# CFLAGS = -Wall -Wextra -Werror 
# NAME = minishell

# OBJS = $(SRCS:.c=.o)

# LIBFT_DIR = ./libft
# LIBFT = $(LIBFT_DIR)/libft.a

# all: $(NAME)

# $(NAME):	$(OBJS)	$(LIBFT)
# 	$(CC)	$(CFLAGS) -lreadline -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include $(OBJS) $(LIBFT) -o $(NAME)

# $(LIBFT):
# 	$(MAKE) -C $(LIBFT_DIR)

# %.o: %.c 
# 	$(CC) $(CFLAGS) -I/opt/homebrew/opt/readline/include -c $< -o $@

# clean:
# 	rm -f $(OBJS) 
# 	$(MAKE) clean -C $(LIBFT_DIR)

# fclean: clean
# 	rm -f $(NAME)
# 	$(MAKE) fclean -C $(LIBFT_DIR)

# re: fclean all

# .PHONY: all bonus clean fclean re