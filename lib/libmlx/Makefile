NOM=libmlx.a
SRC= src/mlx_shaders.c src/mlx_new_window.m src/mlx_init_loop.m src/mlx_new_image.m src/mlx_xpm.c src/mlx_int_str_to_wordtab.c
SRC+= src/mlx_png.c src/mlx_mouse.m
CPPFLAGS    	:= -MMD -MP -I include
CPPFLAGS    	+= -I .
OBJ1=$(SRC:.c=.o)
OBJ=$(OBJ1:.m=.o)
CFLAGS+=-O2

# add to match string put with X11 in size and position
# CFLAGS+= -DSTRINGPUTX11 -fsanitize=address
CFLAGS+= -DSTRINGPUTX11
# CFLAGS+= -DSTRINGPUTX11

all: $(NOM)

$(NOM):	$(OBJ)
	ar -r $(NOM) $(OBJ)
	ranlib $(NOM)

clean:
	rm -f $(NOM) $(OBJ) *~
	rm -f mlx_app

re: clean all
