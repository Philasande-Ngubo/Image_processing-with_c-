findcomp: a.o b.o c.o
	g++ a.o b.o c.o -o findcomp
	
test: a.o b.o d.o
	g++ a.o b.o d.o -o test

a.o:
	g++ -c PGMimage.cpp -o a.o

b.o:
	g++ -c PGMimageProcessor.cpp -o b.o

c.o:
	g++ -c Main.cpp -o c.o

d.o:
	g++ -c Tests.cpp -o d.o


clean:
	rm -f *.o
	@if [ -f findcomp ]; then\
		rm findcomp;\
	else\
		continue;\
	fi
	
	@if [ -f test ]; then\
		rm test;\
	else\
		continue;\
	fi
   

