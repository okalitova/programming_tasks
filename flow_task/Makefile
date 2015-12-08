.PHONY: clean all
all: main clean
main: graph.o maxflow.o preflow.o bfs.o blockflow.o maxflowdinic.o main.o 
	g++ -o main $^
%.o: %.cpp
	g++ -c $^ 
clean:
	rm *.o
