NAME		:=	minirt

LIBS		:=	ft
LIBFT_TARGET:=	lib/libft/libft.a

# Add the path to the MLX library here
MLX_LIB_DIR	:=	lib/libmlx

INCS		= 	include    \
				lib/libft/include    \
				lib/libmlx/include

SRC_DIR		:=	src

SRCS        :=	main.c	\
				parser/parse.c	\
				per_pixal.c 	\
                utils/init.c	\
				utils/init_vec.c	\
				utils/keys.c	\
				utils/utils.c	\
				init/camera.c \
				init/light_init.c \
				init/light.c \
				shapes/cone.c	\
				shapes/cylinder.c	\
				shapes/plane.c	\
				shapes/sphere.c	\
				mat_cal/matrix.c	\
				mat_cal/rotation.c	\
# shapes/sphere.c	\

SRCS        := $(SRCS:%=$(SRC_DIR)/%)

BUILD_DIR   := .build
OBJS        := $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS        := $(OBJS:.o=.d)

# CC          := gcc

# remove -w at the end of project;
# CFLAGS      := -Wall -Wextra -Werror -g -fsanitize=address $(DFLAGS)
# CFLAGS      := -Wall -Wextra -Werror -w -O3 $(DFLAGS)
# CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
# LDFLAGS     := -fsanitize=address $(addprefix -L,$(dir $(LIBFT_TARGET))) -L$(MLX_LIB_DIR)  # Add MLX library directory
# LDLIBS      := $(addprefix -l,$(LIBS)) -lmlx  # Link against MLX library
# MLXFLAGS    := -L$(MLX_LIB_DIR) -lmlx -framework OpenGL -framework AppKit  # MLX-specific flags
# RLFLAGS     := -lreadline

CC          := gcc
CFLAGS      := -Wall -Wextra -Werror -g -w -O3 $(DFLAGS)
CPPFLAGS    := $(addprefix -I,$(INCS)) -MMD -MP
LDFLAGS     := $(addprefix -L,$(dir $(LIBFT_TARGET))) -L$(MLX_LIB_DIR)  # Add MLX library directory
LDLIBS      := $(addprefix -l,$(LIBS)) -lmlx  # Link against MLX library
MLXFLAGS    := -L$(MLX_LIB_DIR) -lmlx -framework OpenGL -framework AppKit  # MLX-specific flags
RLFLAGS     := -lreadline

RM          := rm -f
MAKEFLAGS   += --silent --no-print-directory
DIR_DUP     = mkdir -p $(@D)

all: $(NAME)

$(NAME): $(LIBFT_TARGET) $(OBJS)
	make all -C lib/libmlx
	$(CC) $(LDFLAGS) $(MLXFLAGS) $(OBJS) $(LDLIBS) -o $(NAME) $(DFLAGS)
	$(call print_linking, $(NAME))

$(LIBFT_TARGET):
	$(MAKE) -C $(@D)

$(OBJS): $(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(DIR_DUP)
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<
	@$(call print_obj,$@)

# cleans only the project.
clean:
	$(RM) $(OBJS) $(DEPS)
	$(call print_clean,$(addsuffix \n,$(OBJS)))

#  lib clean, clean all library objects.
lclean:
	for f in $(dir $(LIBFT_TARGET)); do echo "${GREEN}Cleaning: ${CYAN} $$f ${NC} $$"; $(MAKE) -C $$f clean; done

# full clean, clean all objects and libraries and binaries
fclean: clean
	for f in $(dir $(LIBFT_TARGET)); do $(MAKE) -C $$f fclean; done
	make clean -C lib/libmlx
	$(RM) $(NAME)
	$(call print_fclean,$(NAME))

re: fclean all

info-%:
	$(MAKE) --dry-run --always-make $* | grep -v "info"
-include $(DEPS)

define print_linking
	echo "${GREEN}Linking:${BLUE} $(or $1, $$1) ${NC}"
endef
define print_fclean
	echo "${BLUE}cleaned:${CYAN} $(or $1, $$1) ${NC}"
endef
define print_clean
	echo "${BLUE}cleaned:\n${YELLOW} $(or $1, $$1) ${NC}"
endef
define print_target
	echo "${GREEN}Compiling:${BLUE} $(or $1, $$1) ${NC}"
endef
define print_obj
	echo "${BLUE}created: ${YELLOW} $(or $1, $$1)${NC}"
endef
.PHONY: re fclean clean lclean all $(LIBFT_TARGET)
.SILENT:

export DFLAGS
export print_linking
export print_fclean
export print_clean
export print_target
export print_obj

# COLORS
export GREEN = \033[1;32m
export YELLOW = \033[0;33m
export BLUE = \033[1;34m
export CYAN = \033[1;36m
export NC = \033[0m
