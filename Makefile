testmalloc: testmalloc.o tinymalloc.o
	g++ -o testmalloc $^

testmalloc.o: testmalloc.cc tinymalloc.h
	g++ -c testmalloc.cc

tinymalloc.o: tinymalloc.c tinymalloc.h
	gcc -c tinymalloc.c

.PHONY: clean
clean:
	rm -rf testmalloc *.o
