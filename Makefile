CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -Werror -O0 -ggdb
INCLUDES=-I KingArthursEditor/include/ -I KingArthursEditor/lib/imgui/ -I KingArthursEditor/lib/linux/SFML-2.5.0/include/ -I KingArthursEditor/lib/linux/sqlite3/include/ -I KingArthursEditor/lib/sol/include/ -I KingArthursEditor/lib/tinydir/include/
LFLAGS=
LIBS=-lGL -lsfml-window -lsfml-graphics -lsfml-system -llua
SRC=KingArthursEditor/src
SRCS_LIB=lib/imgui/imgui.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_impl.cpp
SRCS=$(shell find ${SRC}/ -type f -iname "*.cpp")
OBJS=$(SRCS:.cpp=.o) $(shell find KingArthursEditor/lib/imgui/ -type f -iname "*.o")
MAIN=kagedit

.PHONY: clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) ${SRC}/*.o $(MAIN)

