CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -O0 -g
TARGET := main

SOURCES := $(wildcard *.cpp)
HEADERS := $(wildcard *.h) $(wildcard *.hpp)

SDL2_CFLAGS := $(shell sdl2-config --cflags)
SDL2_LIBS := $(shell sdl2-config --libs)
SDL2_IMAGE_CFLAGS := $(shell pkg-config --cflags SDL2_image)
SDL2_IMAGE_LIBS := $(shell pkg-config --libs SDL2_image)
SDL2_TTF_CFLAGS := $(shell pkg-config --cflags SDL2_ttf)
SDL2_TTF_LIBS := $(shell pkg-config --libs SDL2_ttf)

$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(SDL2_CFLAGS) $(SDL2_IMAGE_CFLAGS) $(SDL2_TTF_CFLAGS) $(CXXFLAGS) $(SOURCES) -o $(TARGET) $(SDL2_LIBS) $(SDL2_IMAGE_LIBS) $(SDL2_TTF_LIBS)

.PHONY: run clean

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)