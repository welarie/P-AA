CC = g++
OBJ = main.o

all: hello

hello: $(OBJ)
	$(CC) $(OBJ) adjacency_list.h  -o lr2
$(OBJ): %.o: %.cpp
	$(CC) -c $< -o $@
clean:
	rm lr2
	rm *.o

