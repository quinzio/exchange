l0702: l0702.o
	gcc -o l0702 l0702.o -lpthread
l0702.o: src/l0702.c
	gcc -Wall -c -g3 src/l0702.c 
clean:
	rm l0702 l0702.o
