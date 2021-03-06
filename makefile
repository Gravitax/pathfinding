# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maboye <maboye@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/07/31 12:01:33 by maboye            #+#    #+#              #
#    Updated: 2019/08/29 15:19:31 by maboye           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BLACK	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PURPLE	=	\033[35m
TUR		=	\033[36m
WHITE	=	\033[37m
END		=	\033[0m

# project
NAME	=	pathfinding
OS		=	$(shell uname)

# directories
SRCDIR	=	./srcs
INCDIR	=	./includes
OBJDIR	=	./obj

# src / obj files
SRC		=	astar.c \
			astar_tools.c \
			display.c \
			event.c \
			main.c \
			nodes.c \
			tools.c \
			dynarray_insert.c \
			dynarray_mem.c \
			dynarray_stack.c \
			dynarray.c

INC		=	pathfinding.h \
			dynarray.h

OBJ		=	$(addprefix $(OBJDIR)/,$(SRC:.c=.o))
HEADER	=	$(addprefix $(INCDIR)/,$(INC))

# compiler
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror #-g3 -fsanitize=address
SDL		=	-lSDL2-2.0

# libft
FT		=	./libft/
FT_LIB	=	$(addprefix $(FT),libft.a)

all: 		obj $(FT_LIB) $(NAME)

obj:
			mkdir -p $(OBJDIR)

$(OBJDIR)/%.o:$(SRCDIR)/%.c $(HEADER)
			@$(CC) $(CFLAGS) $(FT_LIB) -I $(INCDIR) $(SDL) -c -o $@ $<

$(FT_LIB):
			@$(MAKE) -C $(FT)
			@echo "${GREEN}[LIBRARY COMPILED]${END}"

$(NAME):	$(OBJ) $(FT_LIB)
			@$(CC) $(CFLAGS) $(OBJ) $(FT_LIB) $(SDL) -lm -lpthread -o $@
			@echo "${GREEN}[$@ COMPILED]${END}"

clean:
			@/bin/rm -rf $(OBJDIR)
			@$(MAKE) -C $(FT) clean
			@echo "${PURPLE}[.o deleted]${END}"

#$(MAKE) -C $(MLX) clean

fclean:		clean
			@/bin/rm -rf $(NAME)
			@$(MAKE) -C $(FT) fclean
			@echo "${RED}[$(NAME) deleted]${END}"
			@echo "${RED}[$(LIB) deleted]${END}"

re:			fclean all

.PHONY:		all clean fclean re
