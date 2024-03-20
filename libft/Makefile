# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nlorion <nlorion@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/02 18:03:30 by awallet           #+#    #+#              #
#    Updated: 2023/01/27 12:37:05 by nlorion          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# .......................... GET NEXT LINE DIR ................................
GNL_DIR											= GNL/
GNL_OBJDIR										= GNL/obj/
LIB												= -I GNL/include/

# .......................... LIBFT SOURCE .....................................
SRC =   ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memmove.c \
		ft_memcmp.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_substr.c \
		ft_memcpy.c \
		ft_memchr.c \
		ft_strlen.c \
		ft_strrchr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_striteri.c \
		ft_strmapi.c \
		ft_itoa.c \
		ft_split.c \

# ................................ LIBFT SOURCE BONUS ................................
BONUS =		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

# ................................ LIBFT OBJECTS ......................................
OBJS = $(SRC:.c=.o)
BONUS_OBJS = $(BONUS:.c=.o)

# ........................ GET NEXT LINE OBJECTS.......................................
GNL_SRC											= get_next_line_bonus.c
GNL_SRCS										= $(addprefix $(GNL_DIR)? $(GNL_SRC))
GNL_OBJ											= $(GNL_SRC:.c=.o)
GNL_OBJS										= $(addprefix $(GNL_OBJDIR), $(GNL_OBJ))
$(GNL_OBJDIR)%.o								: $(GNL_DIR)%.c
													@mkdir -p $(GNL_OBJDIR)
													@$(CC) $(CFLAGS) -c $< -o $@
													
# ........................ COMPILER ..................................................
COMPILER_COMMAND = gcc

AR = ar rcs

RM = rm -f

CFLAGS = -Wall -Werror -Wextra

.c.o = $(COMPILER_COMMAND) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS) $(GNL_OBJS)
	$(AR) $(NAME) $(OBJS) $(GNL_OBJS)

all:	$(NAME)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS) $(GNL_OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

bonus:	$(OBJS) $(BONUS_OBJS)
	$(AR) $(NAME) $(OBJS) $(BONUS_OBJS) 

.PHONY : all bonus clean fclean re
