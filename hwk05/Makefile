FLAGS = -pthread
INCLUDES = ../include

all: h5-p1-nolock h5-p1-onelock h5-p1-twolocks h5-p2

clean:
	rm -f h5-p1-nolock h5-p1-onelock h5-p1-twolocks h5-p2

h5-p1-nolock: h5-p1-nolock.c
	gcc -I $(INCLUDES) -o h5-p1-nolock h5-p1-nolock.c $(FLAGS)

h5-p1-onelock: h5-p1-onelock.c
	gcc -I $(INCLUDES) -o h5-p1-onelock h5-p1-onelock.c $(FLAGS)

h5-p1-twolocks: h5-p1-twolocks.c
	gcc -I $(INCLUDES) -o h5-p1-twolocks h5-p1-twolocks.c $(FLAGS)

h5-p2: h5-p2.c
	gcc -I $(INCLUDES) -o h5-p2 h5-p2.c $(FLAGS)