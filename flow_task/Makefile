.PHONY: clean all
all: max_flow clean
max_flow: preflow.o preflow.h flowbfs.o flowbfs.h blockflow.o blockflow.h graph.o graph.h maxflowdinic.o maxflowdinic.h main.o
	g++ -o max_flow $^
%.o: %.c
	g++ -c $^ 
clean:
	rm *.o
