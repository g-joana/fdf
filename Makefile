all: 
	cc *.c minilibx-linux/libmlx_Linux.a -Imlx_linux -lXext -lX11 -o fdf
