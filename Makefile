build:
	gcc -shared -fPIC bi.c -o game.so \
	-I/usr/include/lua5.4 \
	-L/usr/lib/x86_64-linux-gnu \
	-llua5.4 \
	$(shell pkg-config --cflags --libs sdl2 SDL2_image SDL2_ttf)

install:
	mkdir -p ~/.local/lib/lua/5.4
	cp game.so ~/.local/lib/lua/5.4/

all: build install
