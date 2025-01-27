INCLUDES = -I./lib/headers -I./src/util
FLAGS = -Wall -fPIC -g $(INCLUDES)
LIBFLAGS = -L./lib/binaries
LDFLAGS = -lGL -lglfw3
CFLAGS = -std=c99
CPPFLAGS = -std=c++0x
CC = g++
OTHER  = lib/headers/shader_constants.h
OBJ = obj/glad.o obj/lbm.o obj/render.o obj/main.o


.PHONY: clean

all: main clean

main: $(OTHER) $(OBJ)
	$(CC) $(FLAGS) $(LIBFLAGS) -o $@ $^ $(LDFLAGS)

obj/main.o: src/main.c
	$(CC) $(FLAGS) -c $(CFLAGS) src/main.c -o $@  

obj/lbm.o: src/app/lbm.c
	$(CC) $(FLAGS) -c $(CFLAGS) $< -o $@

obj/render.o: src/graphics/render.cpp
	$(CC) $(FLAGS) -c $(CPPFLAGS) $< -o $@

obj/glad.o: lib/headers/glad.c lib/headers/shader_constants.h
	$(CC) $(FLAGS) -c $(CFLAGS) $< -o $@

lib/headers/shader_constants.h: src/graphics/shaders/vertex.glsl src/graphics/shaders/fragment.glsl
	bash -c "xxd -i src/graphics/shaders/vertex.glsl | tac | sed '3s/$$/, 0x00/' | tac > lib/headers/shader_constants.h"
	bash -c "xxd -i src/graphics/shaders/fragment.glsl | tac | sed '3s/$$/, 0x00/' | tac >> lib/headers/shader_constants.h"

clean:
	rm -f $(OBJ) $(OTHER)