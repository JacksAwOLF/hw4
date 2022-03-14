EXEC = view
SCENE = testscenes/scene2.test
OUTPUT = output/test2.ppm
SRC = sources
OBJ = objfiles
HEAD = headers

CC = g++
CFLAGS = -std=c++11
INCFLAGS = -I $(HEAD)
LDFLAGS =

ALL_OBJ_FILES = $(OBJ)/main.o $(OBJ)/obj.o $(OBJ)/ppm.o $(OBJ)/readfile.o $(OBJ)/scene.o $(OBJ)/v3.o $(OBJ)/color.o $(OBJ)/transform.o
ALL_H_FILES = $(HEAD)/obj.h $(HEAD)/ppm.h $(HEAD)/scene.h $(HEAD)/v3.h

all: $(ALL_OBJ_FILES) $(ALL_H_FILES)
	$(CC) -o $(EXEC) $(ALL_OBJ_FILES) $(CFLAGS) $(INCFLAGS) $(LDFLAGS)
	# ./$(EXEC) $(SCENE) $(OUTPUT)

$(OBJ)/main.o: main.cpp $(OBJ)/obj.o $(OBJ)/ppm.o $(OBJ)/readfile.o $(OBJ)/scene.o $(OBJ)/v3.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c main.cpp -o $(OBJ)/main.o

$(OBJ)/color.o: $(SRC)/color.cpp $(HEAD)/color.h $(OBJ)/v3.o $(OBJ)/obj.o 
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC)/color.cpp -o $(OBJ)/color.o
$(OBJ)/obj.o: $(SRC)/obj.cpp $(HEAD)/obj.h $(OBJ)/v3.o $(OBJ)/scene.o $(OBJ)/transform.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC)/obj.cpp -o $(OBJ)/obj.o
$(OBJ)/ppm.o: $(SRC)/ppm.cpp $(HEAD)/ppm.h $(OBJ)/v3.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC)/ppm.cpp -o $(OBJ)/ppm.o
$(OBJ)/readfile.o: $(SRC)/readfile.cpp $(HEAD)/readfile.h $(OBJ)/obj.o $(OBJ)/scene.o $(OBJ)/transform.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC)/readfile.cpp -o $(OBJ)/readfile.o
$(OBJ)/scene.o: $(SRC)/scene.cpp $(HEAD)/scene.h $(OBJ)/v3.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC)/scene.cpp -o $(OBJ)/scene.o
$(OBJ)/v3.o: $(SRC)/v3.cpp $(HEAD)/v3.h
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC)/v3.cpp -o $(OBJ)/v3.o
$(OBJ)/transform.o: $(SRC)/transform.cpp $(HEAD)/transform.h $(OBJ)/v3.o
	$(CC) $(CFLAGS) $(INCFLAGS) -c $(SRC)/transform.cpp -o $(OBJ)/transform.o