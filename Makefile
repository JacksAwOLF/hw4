EXEC = view
SRC = sources
OBJ = objfiles
HEAD = headers

CC = g++
CFLAGS = -std=c++11 -Wall -g
INCFLAGS = -I $(HEAD) -I lodepng/
LDFLAGS = 

CPPFILES = $(foreach dir, $(SRC)/, $(notdir $(wildcard $(SRC)/*.cpp)))
CPP = $(addprefix $(SRC)/, $(CPPFILES))
OBJFILES = $(addprefix $(OBJ)/, $(CPPFILES:.cpp=.o))
HFILES = $(addprefix $(HEAD)/, $(CPPFILES:.cpp=.h))

REMFILES = main.cpp ppm.cpp readfile.cpp lodepng/lodepng.cpp

# TODO: idk why this compiles all the time
all: $(OBJFILES)
	$(CC) -lomp -o $(EXEC) $(REMFILES) $(OBJFILES) $(CFLAGS) $(INCFLAGS) $(LDFLAGS)

# TODO: idk why i need this
$(OBJ)/Light.o: $(HEAD)/Intersection.h

# implicit rule
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) -Xpreprocessor -fopenmp $(CFLAGS) $(INCFLAGS) -c $< -o $(OBJ)/$*.o