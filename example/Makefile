CC = g++
INCLUDES = -I../include
LIBS = -L../lib -lmatrix
CFLAGS = $(INCLUDES) -g

EXECUTABLES = norm proj4

.PHONY: all clean

all: $(EXECUTABLES)

norm: norm.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

proj4: proj4.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
		
clean:
	rm -f *.o $(EXECUTABLES)
	
%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@
	
