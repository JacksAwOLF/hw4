EXEC = view
SRC = sources
OBJ = objfiles
HEAD = headers

CC = g++
CFLAGS = -std=c++11 -Wall
INCFLAGS = -I $(HEAD)
LDFLAGS =

CPPFILES = $(foreach dir, $(SRC)/, $(notdir $(wildcard $(SRC)/*.cpp)))
OBJFILES = $(addprefix $(OBJ)/, $(CPPFILES:.cpp=.o))
HFILES = $(addprefix $(HEAD)/, $(CPPFILES:.cpp=.h))

REMFILES = main.cpp ppm.cpp readfile.cpp

# TODO: idk why this compiles all the time
all: $(OBJFILES)
	$(CC) -o $(EXEC) $(REMFILES) $(OBJFILES) $(CFLAGS) $(INCFLAGS) $(LDFLAGS)

# TODO: idk why i need this
$(OBJ)/Light.o: $(HEAD)/Intersection.h

# implicit rule
$(OBJ)/%.o: $(SRC)/%.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $(OBJ)/$*.o