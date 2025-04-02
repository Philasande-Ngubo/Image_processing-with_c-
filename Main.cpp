#include <iostream>
#include <string>
#include "PGMimageProcessor.h"


int main(){
	
	PGMimage image;
	image.read("Birds.pgm"); 
	
	int wdt, ht;
	image.getDims(wdt, ht); 
	PGMimageProcessor imageProcessor(wdt, ht);
	
	imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()), 160);
	return 0;
}