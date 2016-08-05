ACLOCAL_AMFLAGS = -I m4

bin_PROGRAMS = game
game_SOURCES = src/main.c src/main.h src/status.c src/status.h
game_LDFLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

maitainer-clean-local:
	rm -rf aclocal.m4 configure Makefile.in autotools m4
