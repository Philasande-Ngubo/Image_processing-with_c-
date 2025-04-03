#include "PGMimageProcessor.h"
#include <iostream>

#define print(x) std::cout<<x<<std::endl;
// -----------------------------------PGMimageProcessor class -----------------------------------------------

PGMimageProcessor::PGMimageProcessor(const PGMimageProcessor& other){
	width = other.width;
	height = other.height;
	
	(*connectedComponents).clear();
	
	for (auto itr = (*other.connectedComponents).begin(); itr != (*other.connectedComponents).end(); ++itr){
		(*connectedComponents).push_back(*itr);
	}
	
}

PGMimageProcessor::PGMimageProcessor(PGMimageProcessor&& other){
	
	width = other.width;
	height = other.height;
	
	(*connectedComponents).clear();
	
	for (auto itr = (*other.connectedComponents).begin(); itr != (*other.connectedComponents).end(); ++itr){
		(*connectedComponents).push_back(*itr);
	}
	
	//now clean the other object 
	other.connectedComponents = nullptr;

}

int PGMimageProcessor::getIndex(std::vector<std::vector<int>> * cons, int num){
	for (int i =0 ; i < cons->size(); ++i){
		
		for (int j =0; j < cons->at(i).size(); ++j ){
			
			if ( cons->at(i).at(j) == num){
				return i;
			}
		}
	}

	return -1;
}

void PGMimageProcessor::add(std::vector<std::vector<int>> * cons, int before, int up){
	
	int index = -1;

	
	for (int i =0 ; i < cons->size(); ++i){
		
		if ( (cons->at(i).size() ==1) && (cons->at(i).at(0) == up )){
			index = i;
		}

		for ( int j = 0; j < cons->at(i).size();++j  ){
			if ( cons->at(i).at(j) == before ){
				cons->at(i).push_back(up);
				break;
			}
		}

	}
	if (index >-1){
			cons->erase( cons->begin() +index +1);
	}
	

}

int PGMimageProcessor::extractComponents(unsigned char * threshold, int minValidSize){
	
	std::cout<<"Extracting connectedComponents ..."<<std::endl;
	int num_Objects = 0;
	
	std::vector<std::vector<int>> conflicts;

	for (int i =0; i < height; ++i ){
		
		for (int j =0; j < width; ++j){
			
			int index = i*width + j;
			
			if ( int(threshold[index]) < minValidSize ){
				threshold[index] = char(0);
				
			}
			else{
				
				int up = -1;
				int before = -1;
				
				if ( i !=0 ){ up =int( threshold[(i-1)*width + j]) ;}
				if (j !=0){ before = int (threshold[index -1]);}
				
				if ( up > 0 ){
					threshold[index] = char(num_Objects);
					
					// check in for the conflicts
					if ( (before > 0) && (before != up) ){
						add(&conflicts, before ,up );
					}
				}
				
				else if (before > 0){
					threshold[index] = char(num_Objects);
				}
				else{
					threshold[index] = char(++num_Objects);
					std::vector<int> conf;
					conf.push_back(num_Objects);
					conflicts.push_back( conf);
				}
			}
		}	
	}
	
	(*connectedComponents).clear();
	std::cout<<conflicts.size()<<std::endl;
	
	for (int i = 0; i <conflicts.size(); ++i){
		(*connectedComponents).push_back( new ConnectedComponent(i));	
	}
	
	
	
	for (int i = 0; i < height*width; ++i){
		int num = int(threshold[i]);
		if (num > 0){
			int index = getIndex(&conflicts, num);
			(*connectedComponents).at(index ) ->add(i);
		}
	}
	
	delete [] threshold;
	std::cout<<"ConnectedComponents succesfully created."<<std::endl;
	
	return  (*connectedComponents).size();
}

int PGMimageProcessor::filterComponentsBySize(int minSize, int maxSize){
	std::cout<<"Filtering components outside the size range...."<<std::endl;
	
	for (auto itr = (*connectedComponents).begin(); itr != (*connectedComponents).end(); ++itr){
		
		int size = (*itr)->get()->size();
		if( (size < maxSize+1) && (minSize < size)){
			(*connectedComponents).erase(itr);
		}
		
	}
	std::cout<<"Filtering components outside the size range complete."<<std::endl;
	return (*connectedComponents).size();
}

bool PGMimageProcessor::writeComponents(const std::string& outFileName){
	
	try{
	unsigned char * outPut = new unsigned char[height*width];
	for (int i = 0; i < height*width ; ++i){ outPut[i] = char(0);}
	for ( auto itr =(*connectedComponents).begin() ; itr != (*connectedComponents).end(); ++itr ){
		
		for ( auto j = (*itr)->get()->begin() ; j !=(*itr)->get()->end() ; ++j){
			
			outPut[*j] = char(255);
		}
	}
	
	image.setImageData(outPut,width,height);
	image.write("test.pgm");
	}
	catch(){
		return false;
	}
	
	return true;
}

int PGMimageProcessor::getLargestSize(void) const{
	return 0;
}

int PGMimageProcessor::getSmallestSize(void) const{
	return 0;
}

void PGMimageProcessor::printComponentData(const ConnectedComponent & theComponent) const{
	int i =0;
}



// -----------------------------------ConnectedComponent class -----------------------------------------------
std::vector<int> * ConnectedComponent::get() const{
	return pixels;
}