Ngubo.exe: a.o b.o c.o
	g++ a.o b.o c.o -o Ngubo.exe

a.o:
	g++ -c PGMimage.cpp -o a.o

b.o:
	g++ -c PGMimageProcessor.cpp -o b.o

c.o:
	g++ -c Main.cpp -o c.o

clean:
	rm *.o
	rm Ngubo.exe
