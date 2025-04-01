#include "PGMimageProcessor.h"

PGMimageProcessor::PGMimageProcessor(PGMimageProcessor&& other){
	width = other.width;
	height = other.height;
	
	connectedComponents->clear();
	
	for (auto itr = other.connectedComponents->begin(); itr != other.connectedComponents->end(); ++itr){
		connectedComponents->push_back(*itr);
	}
	
}
PGMimageProcessor::PGMimageProcessor(PGMimageProcessor& other){
	
	width = other.width;
	height = other.height;
	
	connectedComponents->clear();
	
	for (auto itr = other.connectedComponents->begin(); itr != other.connectedComponents->end(); ++itr){
		connectedComponents->push_back(*itr);
	}
	
	//now clean the other object 
	other.connectedComponents = nullptr;

}

