Ngubo.exe: a.o b.o c.o
	g++ a.o b.o c.o -o Ngubo.exe
	

a.o:
	g++ -c PGMimage.cpp -o a.o

b.o:
	g++ -c PGMimageProcessor.cpp -o b.o

c.o:
	g++ -c Main.cpp -o c.o

run:
	./Ngubo.exe

w_run:
	Ngubo
	
w_clean:
	del a.o
	del b.o
	del c.o
	del Ngubo.exe


clean:
	rm *.o
	rm Ngubo.exe

