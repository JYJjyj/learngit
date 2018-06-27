.PHONY:clean

pipe:pipe.o
	gcc $^ -o $@
%.o:%.c
	gcc -c $^ -o $@

clean:
	rm -rf *.o pipe
