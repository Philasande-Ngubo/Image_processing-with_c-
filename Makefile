findcomp: a.o b.o e.o c.o 
	@g++ a.o b.o e.o c.o  -o findcomp
	@echo "findcomp created";
	
test: a.o b.o e.o d.o 
	@g++ a.o b.o d.o e.o -o test
	@echo "test created ";

a.o:
	@g++ -c PGMimage.cpp -o a.o

b.o:
	@g++ -c PGMimageProcessor.cpp -o b.o

c.o:
	@g++ -c Main.cpp -o c.o

d.o:
	@g++ -c Tests.cpp -o d.o

e.o:
	@g++ -c PPMimage.cpp -o e.o


clean:

	@-rm *.o
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

	@echo "Cleaned !!!";\

   

