#OBJS specifies which files to compile as part of the project
OBJS = Source/Zengine.cpp 

#CC specifies which compiler we're usinng
CC = g++

#COMPILER_FLAGS specifies the addition comilation options we're using
#-w suppresses all warnings
COMPILER_FLAGS = -w

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lGLU -lGL -lm -DGL_GLEXT_PROTOTYPES 

#OBJ_NAME specifies the name of the executable
OBJ_NAME = Zengine

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS)  -o $(OBJ_NAME)