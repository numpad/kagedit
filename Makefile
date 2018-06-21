CC=g++
CFLAGS=-std=c++14 -Wall -pedantic -ggdb
INCLUDES=-I KingArthursEditor/lib/imgui/ -I KingArthursEditor/lib/linux/SFML-2.5.0/include/ -I KingArthursEditor/lib/linux/sqlite3/include/
LFLAGS=
LIBS=-lGL -lsfml-window -lsfml-graphics -lsfml-system
SRC=KingArthursEditor
SRCS_LIB=lib/imgui/imgui.cpp lib/imgui/imgui_draw.cpp lib/imgui/imgui_impl.cpp
SRCS=$(shell find ${SRC}/ -type f -iname "*.cpp")
OBJS=$(SRCS:.cpp=.o)
MAIN=kagedit

.PHONY: clean

all: $(MAIN)

$(MAIN): $(OBJS)
	$(CC) $(CLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) ${SRC}/*.o $(MAIN)

