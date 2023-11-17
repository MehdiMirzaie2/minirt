NAME			:=	libft.a

SRC_DIR			:=	src
SRCS			:=	src/ft_isalnum.c src/ft_isprint.c src/ft_memcmp.c src/ft_putchar_fd.c src/ft_split.c \
					src/ft_strlcat.c src/ft_strncmp.c src/ft_substr.c src/ft_atoi.c src/ft_isalpha.c \
					src/ft_itoa.c src/ft_memcpy.c  src/ft_putendl_fd.c src/ft_strchr.c  src/ft_strlcpy.c \
					src/ft_strnstr.c src/ft_tolower.c src/ft_bzero.c src/ft_isascii.c \
					src/ft_memmove.c src/ft_putnbr_fd.c src/ft_strdup.c src/ft_strlen.c src/ft_strrchr.c \
					src/ft_toupper.c src/ft_calloc.c src/ft_isdigit.c src/ft_memchr.c src/ft_memset.c  \
					src/ft_putstr_fd.c src/ft_strjoin.c src/ft_strmapi.c src/ft_strtrim.c src/ft_striteri.c \
					src/ft_lstnew.c src/ft_lstadd_front.c src/ft_lstsize.c src/ft_lstlast.c \
					src/ft_lstadd_back.c src/ft_lstdelone.c src/ft_lstclear.c src/ft_lstiter.c \
					src/get_next_line_utils.c src/get_next_line.c src/ft_atof.c src/ft_space.c src/ft_sscanf.c

BUILD_DIR   	:= .build
OBJS        	:= $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        	:= $(OBJS:.o=.d)

CC          	:= clang
# CFLAGS      	:= -Wall -Wextra -Werror -g -fsanitize=address
CFLAGS      	:= -Wall -Wextra -Werror
# CFLAGS      	:= -Wall -Wextra -Werror -g
CPPFLAGS    	:= -MMD -MP -I include
AR          	:= ar
ARFLAGS     	:= -r -c -s

RM          	:= rm -f
MAKEFLAGS   	+= --no-print-directory
DIR_DUP     	= mkdir -p $(@D)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)
	$(info CREATED $(NAME))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	$(info CREATED $@)

-include $(DEPS)

clean:
	$(RM) $(OBJS) $(DEPS)

fclean: clean
	$(RM) $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: clean fclean re
.SILENT:
