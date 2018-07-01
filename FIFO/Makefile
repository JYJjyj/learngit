.PHONY:all
all:writer reader

writer:FIFOpipe.c
	gcc $^ -o $@

reader:Reader.c
	gcc $^ -o $@

.PHONY:clean
clean:
	rm -f writer reader *.o
