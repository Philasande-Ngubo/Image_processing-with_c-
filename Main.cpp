// Philasande Ngubo (NGBPHI016)
// Date: 1/04/2024
// University of Cape Town
// (c) 2025

#include <iostream>
#include <string>
#include "PGMimageProcessor.h"


int main(){
	
	PGMimage image;
	image.read("blu.pgm"); 
	
	int wdt, ht;
	image.getDims(wdt, ht); 
	PGMimageProcessor imageProcessor(wdt, ht);
	
	std::cout<<"Number of connectedComponents components :"<<imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()), 80)<<std::endl;
	std::cout<<"Max:"<<imageProcessor.getLargestSize()<<std::endl;
	std::cout<<"Min:"<<imageProcessor.getSmallestSize()<<std::endl;
	//imageProcessor.filterComponentsBySize(5000,6766);
	//std::cout<<"Max:"<<imageProcessor.getLargestSize()<<std::endl;
	//std::cout<<"Min:"<<imageProcessor.getSmallestSize()<<std::endl;
	imageProcessor.writeComponents("itest.pgm");
	return 0;
}