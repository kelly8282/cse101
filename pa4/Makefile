SRC1	= MatrixTest.c Matrix.c List.c
SRC2	= ListClient.c List.c
SRC3	= ListTest.c List.c
SRC4	= MatrixClient.c Matrix.c List.c
SRC5	= Sparse.c Matrix.c List.c
OBJ1	= $(SRC1:%.c=%.o)
OBJ2	= $(SRC2:%.c=%.o)
OBJ3	= $(SRC3:%.c=%.o)
OBJ4	= $(SRC4:%.c=%.o)
OBJ5	= $(SRC5:%.c=%.o)

CFLAGS	= -std=c17 -Wall

MatrixTest: $(OBJ1)
	gcc $(CFLAGS) -o $@ $^

ListClient: $(OBJ2)
	gcc $(CFLAGS) -o $@ $^

ListTest: $(OBJ3)
	gcc $(CFLAGS) -o $@ $^

MatrixClient: $(OBJ4)
	gcc $(CFLAGS) -o $@ $^

Sparse: $(OBJ5)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f $(OBJ5) $(OBJ4) $(OBJ3) $(OBJ2) $(OBJ1) Sparse MatrixClient ListTest ListClient MatrixTest

format:
	clang-format -i -style=file *.[ch]



