// Philasande Ngubo (NGBPHI016)
// Date: 1/04/2024
// University of Cape Town
// (c) 2025

#include <iostream>
#include <string>
#include "PGMimageProcessor.h"
#include <algorithm>
#include <cctype>

bool isPGM(std::string file){
	int size = file.size();

	if ( file.size() > 4){
		return file.substr(size-4,4) == ".pgm";
	}
	return false;
	
}

bool isValid(){

	int m =0;
	int f =0;
	int t =0;
	int p =0;
	int w =0;
	int m =0;
	int m =0;

	return true;
}

void run(int charc, char ** charv){

	

	if ( charc > 1){

		std::string input = charv[1];

		if ( isPGM(input) ){

		}else{
			std::cout<< "Expected a pgm image as a first agurment but none was provided."<<std::endl;
		}
	}
	else{
		std::cout<< "Expected arguments but none were provided."<<std::endl;
	}
}




int main(int charc, char ** charv){

	for( int i = 1; i < charc;++i){
		std::cout<<charv[i]<<",";
	}
	std::cout<<"\n";

	run(charc,charv);
	//PGMimage image;
	//image.read("blu.pgm"); 
	
	/*int wdt, ht;
	image.getDims(wdt, ht); 
	PGMimageProcessor imageProcessor(wdt, ht);
	
	std::cout<<"Number of connectedComponents components :"<<imageProcessor.extractComponents( const_cast<unsigned char *>(image.getBuffer()), 80)<<std::endl;
	std::cout<<"Max:"<<imageProcessor.getLargestSize()<<std::endl;
	std::cout<<"Min:"<<imageProcessor.getSmallestSize()<<std::endl;
	//imageProcessor.filterComponentsBySize(5000,6766);
	//std::cout<<"Max:"<<imageProcessor.getLargestSize()<<std::endl;
	//std::cout<<"Min:"<<imageProcessor.getSmallestSize()<<std::endl;
	imageProcessor.writeComponents("itest.pgm");*/
	return 0;
}