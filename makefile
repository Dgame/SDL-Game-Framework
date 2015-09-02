EXT_DIR = extlibs
FRAMEWORK_DIR = SDL\src

FRAMEWORK_FILES = $(FRAMEWORK_DIR)\Window.cpp $(FRAMEWORK_DIR)\Color.cpp  $(FRAMEWORK_DIR)\Vector2.cpp $(FRAMEWORK_DIR)\Rect.cpp \
  $(FRAMEWORK_DIR)\Texture.cpp $(FRAMEWORK_DIR)\Renderer.cpp $(FRAMEWORK_DIR)\Event.cpp \
  $(FRAMEWORK_DIR)\Surface.cpp $(FRAMEWORK_DIR)\Timer.cpp $(FRAMEWORK_DIR)\Font.cpp

TEST_FILES = main.cpp

OBJS = $(TEST_FILES) $(FRAMEWORK_FILES)
CC = g++

INCLUDE_PATHS = -I $(EXT_DIR)\SDL2-2.0.3\include \
				-I $(EXT_DIR)\SDL2_image-2.0.0\include\SDL2 \
				-I $(EXT_DIR)\SDL2_ttf-2.0.12\x86_64-w64-mingw32\include\SDL2 \
				-I SDL\include \
				-I SDL
LIBRARY_PATHS = -L $(EXT_DIR)\SDL2-2.0.3\lib\x86 \
				-L $(EXT_DIR)\SDL2_image-2.0.0\lib \
				-L $(EXT_DIR)\SDL2_ttf-2.0.12\i686-w64-mingw32\lib

COMPILER_WARNINGS = -Wall -Wnon-virtual-dtor -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wmain -Wzero-as-null-pointer-constant -Wextra -pedantic -Wfatal-errors -Wno-switch
COMPILER_FLAGS = -std=c++1y
COMPILER_FLAGS_DEBUG = -g
COMPILER_FLAGS_RELEASE = -O3

LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf

OBJ_NAME = main

all:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
debug:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(COMPILER_FLAGS_DEBUG) $(LINKER_FLAGS) -o $(OBJ_NAME)
release:
	$(CC) $(OBJS) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_WARNINGS) $(COMPILER_FLAGS) $(COMPILER_FLAGS_RELEASE) $(LINKER_FLAGS) -o $(OBJ_NAME)
