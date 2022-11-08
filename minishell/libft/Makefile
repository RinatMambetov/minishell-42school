NAME	=	libft.a
CFLAGS	=	-Wall -Wextra -Werror
HEAD	=	libft.h
AR		=	ar rc
RM		=	rm -rf

SRC	=	ft_memset.c\
		ft_bzero.c\
		ft_memcpy.c\
		ft_memccpy.c\
		ft_memmove.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_strdup.c\
		ft_strlen.c\
		ft_strlcpy.c\
		ft_strlcat.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strnstr.c\
		ft_strncmp.c\
		ft_strcmp.c\
		ft_atoi.c\
		ft_calloc.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_tolower.c\
		ft_strmapi.c\
		ft_substr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_split.c\
		ft_itoa.c\
		ft_putchar_fd.c\
		ft_putstr_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\

OBJ		=	$(SRC:.c=.o)

$(NAME): ${OBJ}
			${AR} ${NAME} ${OBJ}
all:	${NAME}

clean:	 
		${RM} ${OBJ}

fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re