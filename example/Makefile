CC = g++
INCLUDES = -I../include
LIBS = -L../lib -lmatrix
CFLAGS = $(INCLUDES) -g

EXECUTABLES = norm pca

.PHONY: all clean

all: $(EXECUTABLES)

norm: norm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

pca: pca.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
		
clean:
	rm -f *.o $(EXECUTABLES)
	
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
	
